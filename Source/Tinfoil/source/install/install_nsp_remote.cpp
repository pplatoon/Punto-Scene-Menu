#include "install/install_nsp_remote.hpp"

namespace tin::install::nsp
{
    NetworkNSPInstallTask::NetworkNSPInstallTask(FsStorageId destStorageId, bool ignoreReqFirmVersion, std::string url) :
        IInstallTask(destStorageId, ignoreReqFirmVersion), m_url(url)
    {

    }

    void NetworkNSPInstallTask::PrepareForInstall()
    {
        
    }

    void NetworkNSPInstallTask::Install()
    {

    }
}