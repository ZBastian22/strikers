// The mod layer.
//
// At startup, after strikers.ini and the STRIKERS_* environment variables have
// been applied, every mod in the mods/ folder next to the executable is
// run, in alphabetical order. A missing or empty folder is fine.
//
// Scripts see one global table, `strikers`:
//
//   strikers.api_version          1
//   strikers.log(text)            writes to the game's log
//   strikers.set(key, value)      sets a config key, exactly as strikers.ini or
//                                 a STRIKERS_* variable would; value may be a
//                                 string, number or boolean
//   strikers.on_indicator(fn)     registers fn to be called for every player's
//                                 overhead team number, every frame. fn gets a
//                                 table: side (1 or 2), digit (what would be
//                                 drawn), has_ball, is_controlled, is_captain.
//                                 It may return a table with any of: digit
//                                 (1-4), size (multiplier), dy (pixels, + is
//                                 down), show (false hides it). Return nothing
//                                 to leave the number as it is.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#else
#include <dirent.h>
#include <sys/stat.h>
#endif

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

#include "NL/nlConfig.h"
#include "port/host.h"

extern "C" void OSReport(const char* msg, ...);

static lua_State* gL = NULL;
static int gIndicatorRef = LUA_NOREF;
static int gIndicatorErrors = 0;

// --------------------------------------------------------------------------
// The API the scripts call.
// --------------------------------------------------------------------------

static int l_log(lua_State* L)
{
    OSReport("[mods] %s\n", luaL_checkstring(L, 1));
    return 0;
}

static int l_set(lua_State* L)
{
    const char* key = luaL_checkstring(L, 1);
    const char* val;
    if (lua_type(L, 2) == LUA_TBOOLEAN)
    {
        val = lua_toboolean(L, 2) ? "1" : "0";
    }
    else
    {
        // Numbers coerce to strings here, which is exactly how the ini file and
        // the environment variables arrive too; the game parses them the same way.
        val = luaL_checkstring(L, 2);
    }
    Config::Global().Set(key, val);
    return 0;
}

static int l_on_indicator(lua_State* L)
{
    luaL_checktype(L, 1, LUA_TFUNCTION);
    if (gIndicatorRef != LUA_NOREF)
    {
        luaL_unref(L, LUA_REGISTRYINDEX, gIndicatorRef);
    }
    lua_pushvalue(L, 1);
    gIndicatorRef = luaL_ref(L, LUA_REGISTRYINDEX);
    return 0;
}

// --------------------------------------------------------------------------
// Finding the scripts.
// --------------------------------------------------------------------------

#define MODS_MAX_FILES 64
#define MODS_NAME_MAX 256

// One mod: either a folder mods/<name>/ holding mod.lua (the convention), or a
// bare mods/<name>.lua (still accepted). A folder may carry a mod.ini next to
// mod.lua with name=, version=, author= and enabled=0/1 lines.
struct ModEntry
{
    char folder[MODS_NAME_MAX];  // entry name in mods/ (folder or file)
    char script[MODS_NAME_MAX];  // "mod.lua" or the bare file name
    int isFolder;
    char name[MODS_NAME_MAX];    // display name (from mod.ini, else the folder)
    char version[64];
    int enabled;
};

static int SortMod(const void* a, const void* b)
{
    return strcmp(((const ModEntry*)a)->folder, ((const ModEntry*)b)->folder);
}

static int FileExists(const char* path)
{
    FILE* f = fopen(path, "rb");
    if (f == NULL) return 0;
    fclose(f);
    return 1;
}

static void TrimLine(char* s)
{
    size_t n = strlen(s);
    while (n > 0 && (s[n - 1] == '\n' || s[n - 1] == '\r' || s[n - 1] == ' ' || s[n - 1] == '\t')) s[--n] = 0;
}

// mod.ini: simple key=value lines, no sections needed.
static void ReadModIni(const char* dir, ModEntry* m)
{
    char path[1400];
    snprintf(path, sizeof path, "%s/mod.ini", dir);
    FILE* f = fopen(path, "rb");
    if (f == NULL) return;
    char line[512];
    while (fgets(line, sizeof line, f) != NULL)
    {
        TrimLine(line);
        char* eq = strchr(line, '=');
        if (eq == NULL || line[0] == ';' || line[0] == '#') continue;
        *eq = 0;
        char* key = line;
        char* val = eq + 1;
        while (*val == ' ' || *val == '\t') ++val;
        TrimLine(key);
        if (strcmp(key, "name") == 0) snprintf(m->name, sizeof m->name, "%s", val);
        else if (strcmp(key, "version") == 0) snprintf(m->version, sizeof m->version, "%s", val);
        else if (strcmp(key, "enabled") == 0) m->enabled = (val[0] != '0' && strcmp(val, "false") != 0 && strcmp(val, "no") != 0);
    }
    fclose(f);
}

static void AddEntry(ModEntry* mods, int* count, const char* folder, const char* entry, int isDir)
{
    if (*count >= MODS_MAX_FILES || entry[0] == '.') return;
    ModEntry* m = &mods[*count];
    memset(m, 0, sizeof *m);
    snprintf(m->folder, sizeof m->folder, "%s", entry);
    snprintf(m->name, sizeof m->name, "%s", entry);
    m->enabled = 1;
    if (isDir)
    {
        char dir[1400];
        snprintf(dir, sizeof dir, "%s/%s", folder, entry);
        static const char* const kEntry[] = { "mod.lua", "main.lua", "init.lua" };
        int found = 0;
        for (int k = 0; k < 3 && !found; ++k)
        {
            char path[1600];
            snprintf(path, sizeof path, "%s/%s", dir, kEntry[k]);
            if (FileExists(path))
            {
                snprintf(m->script, sizeof m->script, "%s", kEntry[k]);
                found = 1;
            }
        }
        if (!found) return; // a folder with no script is not a mod
        m->isFolder = 1;
        ReadModIni(dir, m);
    }
    else
    {
        size_t len = strlen(entry);
        if (len <= 4 || strcmp(entry + len - 4, ".lua") != 0) return;
        snprintf(m->script, sizeof m->script, "%s", entry);
    }
    ++*count;
}

static int ListMods(const char* folder, ModEntry* mods)
{
    int count = 0;

#ifdef _WIN32
    char pattern[1200];
    snprintf(pattern, sizeof pattern, "%s\\*", folder);
    WIN32_FIND_DATAA fd;
    HANDLE h = FindFirstFileA(pattern, &fd);
    if (h != INVALID_HANDLE_VALUE)
    {
        do
        {
            AddEntry(mods, &count, folder, fd.cFileName, (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0);
        } while (FindNextFileA(h, &fd));
        FindClose(h);
    }
#else
    DIR* d = opendir(folder);
    if (d != NULL)
    {
        struct dirent* e;
        while ((e = readdir(d)) != NULL)
        {
            char path[1400];
            snprintf(path, sizeof path, "%s/%s", folder, e->d_name);
            struct stat st;
            int isDir = (stat(path, &st) == 0 && S_ISDIR(st.st_mode));
            AddEntry(mods, &count, folder, e->d_name, isDir);
        }
        closedir(d);
    }
#endif

    qsort(mods, (size_t)count, sizeof(ModEntry), SortMod);
    return count;
}

// --------------------------------------------------------------------------
// Startup.
// --------------------------------------------------------------------------

extern "C" void PortModsInit(void)
{
    char dir[1024];
    if (port_executable_dir(dir, sizeof dir) != 0)
    {
        dir[0] = '.';
        dir[1] = '\0';
    }

    char folder[1100];
    snprintf(folder, sizeof folder, "%s/mods", dir);

    static ModEntry mods[MODS_MAX_FILES];
    int count = ListMods(folder, mods);
    if (count == 0)
    {
        OSReport("[mods] no mods in %s\n", folder);
        return;
    }

    gL = luaL_newstate();
    if (gL == NULL)
    {
        OSReport("[mods] could not start the script engine\n");
        return;
    }
    luaL_openlibs(gL);

    lua_newtable(gL);
    lua_pushcfunction(gL, l_log);
    lua_setfield(gL, -2, "log");
    lua_pushcfunction(gL, l_set);
    lua_setfield(gL, -2, "set");
    lua_pushcfunction(gL, l_on_indicator);
    lua_setfield(gL, -2, "on_indicator");
    lua_pushinteger(gL, 1);
    lua_setfield(gL, -2, "api_version");
    lua_setglobal(gL, "strikers");

    int loaded = 0;
    for (int i = 0; i < count; ++i)
    {
        ModEntry* m = &mods[i];
        if (!m->enabled)
        {
            OSReport("[mods] %s is disabled (mod.ini)\n", m->name);
            continue;
        }
        char modDir[1400];
        char full[1700];
        if (m->isFolder)
        {
            snprintf(modDir, sizeof modDir, "%s/%s", folder, m->folder);
            snprintf(full, sizeof full, "%s/%s", modDir, m->script);
        }
        else
        {
            snprintf(modDir, sizeof modDir, "%s", folder);
            snprintf(full, sizeof full, "%s/%s", folder, m->script);
        }

        // strikers.mod_dir / strikers.mod_name tell a script where it lives.
        lua_getglobal(gL, "strikers");
        lua_pushstring(gL, modDir);
        lua_setfield(gL, -2, "mod_dir");
        lua_pushstring(gL, m->name);
        lua_setfield(gL, -2, "mod_name");
        lua_pop(gL, 1);

        if (m->version[0] != 0)
            OSReport("[mods] loading %s %s (%s)\n", m->name, m->version, m->folder);
        else
            OSReport("[mods] loading %s (%s)\n", m->name, m->folder);
        if (luaL_dofile(gL, full) != LUA_OK)
        {
            OSReport("[mods] ERROR in %s: %s\n", m->name, lua_tostring(gL, -1));
            lua_pop(gL, 1);
            continue;
        }
        ++loaded;
    }
    OSReport("[mods] %d mod(s) loaded\n", loaded);
}

// --------------------------------------------------------------------------
// The indicator door, called by Indicators.cpp for each number each frame.
// Returns 1 if the script changed anything.
// --------------------------------------------------------------------------

extern "C" int PortModsIndicator(int side, int digit, int hasBall, int isControlled, int isCaptain,
    int* pDigit, float* pSize, float* pDy, int* pShow)
{
    if (gL == NULL || gIndicatorRef == LUA_NOREF || gIndicatorErrors >= 8)
    {
        return 0;
    }

    lua_rawgeti(gL, LUA_REGISTRYINDEX, gIndicatorRef);
    lua_createtable(gL, 0, 5);
    lua_pushinteger(gL, side + 1);
    lua_setfield(gL, -2, "side");
    lua_pushinteger(gL, digit);
    lua_setfield(gL, -2, "digit");
    lua_pushboolean(gL, hasBall);
    lua_setfield(gL, -2, "has_ball");
    lua_pushboolean(gL, isControlled);
    lua_setfield(gL, -2, "is_controlled");
    lua_pushboolean(gL, isCaptain);
    lua_setfield(gL, -2, "is_captain");

    if (lua_pcall(gL, 1, 1, 0) != LUA_OK)
    {
        OSReport("[mods] indicator handler error: %s\n", lua_tostring(gL, -1));
        lua_pop(gL, 1);
        if (++gIndicatorErrors >= 8)
        {
            OSReport("[mods] indicator handler disabled after repeated errors\n");
        }
        return 0;
    }

    int changed = 0;
    if (lua_istable(gL, -1))
    {
        lua_getfield(gL, -1, "digit");
        if (lua_isnumber(gL, -1))
        {
            *pDigit = (int)lua_tointeger(gL, -1);
            changed = 1;
        }
        lua_pop(gL, 1);

        lua_getfield(gL, -1, "size");
        if (lua_isnumber(gL, -1))
        {
            *pSize = (float)lua_tonumber(gL, -1);
            changed = 1;
        }
        lua_pop(gL, 1);

        lua_getfield(gL, -1, "dy");
        if (lua_isnumber(gL, -1))
        {
            *pDy = (float)lua_tonumber(gL, -1);
            changed = 1;
        }
        lua_pop(gL, 1);

        lua_getfield(gL, -1, "show");
        if (lua_isboolean(gL, -1))
        {
            *pShow = lua_toboolean(gL, -1);
            changed = 1;
        }
        lua_pop(gL, 1);
    }
    lua_pop(gL, 1);
    return changed;
}
