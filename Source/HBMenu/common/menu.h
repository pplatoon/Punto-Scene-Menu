#pragma once

#define ENTRY_NAMELENGTH   0x200
#define ENTRY_AUTHORLENGTH 0x100
#define ENTRY_VERLENGTH   0x10
#define ENTRY_ARGBUFSIZE 0x400

typedef enum
{
    ENTRY_TYPE_FILE,
    ENTRY_TYPE_FOLDER,
} MenuEntryType;

typedef struct menuEntry_s_tag menuEntry_s;
typedef struct menu_s_tag menu_s;

struct menu_s_tag
{
    menuEntry_s *firstEntry, *lastEntry;
    int nEntries;
    int curEntry;

    char dirname[PATH_MAX+1];
};

typedef struct
{
    char* dst;
    uint32_t buf[ENTRY_ARGBUFSIZE/sizeof(uint32_t)];
} argData_s;

struct menuEntry_s_tag
{
    menu_s* menu;
    menuEntry_s* next;
    MenuEntryType type;

    char path[PATH_MAX+1];
    argData_s args;

    char name[ENTRY_NAMELENGTH+1];
    char author[ENTRY_AUTHORLENGTH+1];
    char version[ENTRY_VERLENGTH+1];

    uint8_t *icon;
    size_t icon_size;
    uint8_t *icon_gfx;

    NacpStruct *nacp;
};

void menuEntryInit(menuEntry_s* me, MenuEntryType type);
void menuEntryFree(menuEntry_s* me);
bool fileExists(const char* path);
bool menuEntryLoad(menuEntry_s* me, const char* name, bool shortcut);
void menuEntryParseIcon(menuEntry_s* me);
void menuEntryParseNacp(menuEntry_s* me);

menu_s* menuGetCurrent(void);
int menuScan(const char* target);

static inline char* getExtension(const char* str)
{
    const char* p;
    for (p = str+strlen(str); p >= str && *p != '.'; p--);
    return (char*)p;
}

static inline char* getSlash(const char* str)
{
    const char* p;
    for (p = str+strlen(str); p >= str && *p != '/'; p--);
    return (char*)p;
}

