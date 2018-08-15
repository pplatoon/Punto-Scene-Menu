#include "util/network_util.hpp"

#include <curl/curl.h>
#include <algorithm>
#include <cstring>
#include <sstream>
#include "error.hpp"

namespace tin::network
{
    // HTTPHeader
 
    HTTPHeader::HTTPHeader(std::string url) :
        m_url(url)
    {

    }

    size_t HTTPHeader::ParseHTMLHeader(char* bytes, size_t size, size_t numItems, void* userData)
    {
        HTTPHeader* header = reinterpret_cast<HTTPHeader*>(userData);
        size_t numBytes = size * numItems;
        std::string line(bytes, numBytes);

        // Remove any newlines or carriage returns
        line.erase(std::remove(line.begin(), line.end(), '\n'), line.end());
        line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());

        // Split into key and value
        if (!line.empty())
        {
            auto keyEnd = line.find(": ");

            if (keyEnd != 0)
            {
                std::string key = line.substr(0, keyEnd);
                std::string value = line.substr(keyEnd + 2);

                // Make key lowercase
                std::transform(key.begin(), key.end(), key.begin(), ::tolower);
                header->m_values[key] = value;
            }
        }

        return numBytes;
    }

    void HTTPHeader::PerformRequest()
    {
        // We don't want any existing values to get mixed up with this request
        m_values.clear();

        CURL* curl = curl_easy_init();
        CURLcode rc = (CURLcode)0;

        if (!curl)
        {
            THROW_FORMAT("Failed to initialize curl\n");
        }

        curl_easy_setopt(curl, CURLOPT_URL, m_url.c_str());
        curl_easy_setopt(curl, CURLOPT_NOBODY, true);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "tinfoil");
        curl_easy_setopt(curl, CURLOPT_HEADERDATA, this);
        curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, &tin::network::HTTPHeader::ParseHTMLHeader);

        rc = curl_easy_perform(curl);
        if (rc != CURLE_OK)
        {
            THROW_FORMAT("Failed to retrieve HTTP Header: %s\n", curl_easy_strerror(rc));
        }

        u64 httpCode = 0;
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
        curl_easy_cleanup(curl);

        if (httpCode != 200 && httpCode != 204)
        {
            THROW_FORMAT("Unexpected HTTP response code when retrieving header: %lu\n", httpCode);
        }
    }

    bool HTTPHeader::HasValue(std::string key)
    {
        return m_values.count(key);
    }

    std::string HTTPHeader::GetValue(std::string key)
    {
        return m_values[key];
    }

    // End HTTPHeader

    // HTTPDownloadBuffer

    HTTPDownloadBuffer::HTTPDownloadBuffer(size_t size, void* buffer) :
        m_totalSize(size), m_buffer(buffer)
    {

    }

    // End HTTPDownloadBuffer

    // HTTPDownload

    HTTPDownload::HTTPDownload(std::string url) :
        m_url(url), m_header(url)
    {

    }

    size_t HTTPDownload::ParseHTMLData(char* bytes, size_t size, size_t numItems, void* userData)
    {
        HTTPDownloadBuffer* downloadBuffer = reinterpret_cast<HTTPDownloadBuffer*>(userData);
        size_t numBytes = size * numItems;

        if (downloadBuffer->m_readSize + numBytes > downloadBuffer->m_totalSize)
        {
            printf("New read size 0x%lx would exceed total expected size 0x%lx\n", downloadBuffer->m_readSize + numBytes, downloadBuffer->m_totalSize);
            return 0;
        }

        memcpy(reinterpret_cast<u8*>(downloadBuffer->m_buffer) + downloadBuffer->m_readSize, bytes, numBytes);
        downloadBuffer->m_readSize += numBytes;

        return numBytes;
    }

    bool HTTPDownload::IsRangesSupported()
    {
        // The header won't be populated until we do this
        m_header.PerformRequest();

        if (m_header.HasValue("accept-ranges"))
        {
            return m_header.GetValue("accept-ranges") == "bytes";
        }

        CURL* curl = curl_easy_init();
        CURLcode rc = (CURLcode)0;

        if (!curl)
        {
            THROW_FORMAT("Failed to initialize curl\n");
        }

        curl_easy_setopt(curl, CURLOPT_URL, m_url.c_str());
        curl_easy_setopt(curl, CURLOPT_NOBODY, true);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "tinfoil");
        curl_easy_setopt(curl, CURLOPT_RANGE, "0-0");

        rc = curl_easy_perform(curl);
        if (rc != CURLE_OK)
        {
            THROW_FORMAT("Failed to retrieve HTTP Header: %s\n", curl_easy_strerror(rc));
        }

        u64 httpCode = 0;
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
        curl_easy_cleanup(curl);

        return httpCode == 206;
    }

    void HTTPDownload::RequestDataRange(void* buffer, size_t offset, size_t size)
    {
        if (!this->IsRangesSupported())
        {
            THROW_FORMAT("Attempted range request when ranges aren't supported!\n");
        }

        HTTPDownloadBuffer downloadBuffer(size, buffer);
        CURL* curl = curl_easy_init();
        CURLcode rc = (CURLcode)0;

        if (!curl)
        {
            THROW_FORMAT("Failed to initialize curl\n");
        }

        std::stringstream ss;
        ss << offset << "-" << (offset + size - 1);
        auto range = ss.str();
        printf("Requesting from range: %s\n", range.c_str());

        curl_easy_setopt(curl, CURLOPT_URL, m_url.c_str());
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "tinfoil");
        curl_easy_setopt(curl, CURLOPT_RANGE, range.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &downloadBuffer);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &tin::network::HTTPDownload::ParseHTMLData);

        rc = curl_easy_perform(curl);
        if (rc != CURLE_OK)
        {
            THROW_FORMAT("Failed to retrieve perform range request: %s\n", curl_easy_strerror(rc));
        }

        u64 httpCode = 0;
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
        curl_easy_cleanup(curl);

        if (httpCode != 206)
        {
            THROW_FORMAT("Failed to request range! Response code is %lu\n", httpCode);
        }

        printf("Data size read: %lx\n", downloadBuffer.m_readSize);
    }

    // End HTTPDownload

    size_t WaitReceiveNetworkData(int sockfd, void* buf, size_t len)
    {
        size_t blockSizeRead = 0;
        size_t sizeRead = 0;

        while ((sizeRead += (blockSizeRead = recv(sockfd, (u8*)buf + sizeRead, len - sizeRead, 0)) < len) && (blockSizeRead > 0 || errno == EAGAIN) && !(hidKeysDown(CONTROLLER_P1_AUTO) & KEY_B))
        {
            hidScanInput();
            errno = 0;
        }

        return sizeRead;
    }

    size_t WaitSendNetworkData(int sockfd, void* buf, size_t len)
    {
        size_t blockSizeWritten = 0;
        size_t sizeWritten = 0;

        while ((sizeWritten += (blockSizeWritten = send(sockfd, (u8*)buf + sizeWritten, len - sizeWritten, 0)) < len) && (blockSizeWritten > 0 || errno == EAGAIN) && !(hidKeysDown(CONTROLLER_P1_AUTO) & KEY_B))
        {
            hidScanInput();
            errno = 0;
        }

        return sizeWritten;
    }
}