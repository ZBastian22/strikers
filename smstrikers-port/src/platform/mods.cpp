// The mod layer.
//
// At startup, after strikers.ini and the STRIKERS_* environment variables have
// been applied, every .lua file in the mods/ folder next to the executable is
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

static int SortName(const void* a, const void* b)
{
    return strcmp((const char*)a, (const char*)b);
}

static int ListLuaFiles(const char* folder, char names[MODS_MAX_FILES][MODS_NAME_MAX])
{
    int count = 0;

#ifdef _WIN32
    char pattern[1200];
    snprintf(pattern, sizeof pattern, "%s\\*.lua", folder);
    WIN32_FIND_DATAA fd;
    HANDLE h = FindFirstFileA(pattern, &fd);
    if (h != INVALID_HANDLE_VALUE)
    {
        do
        {
            if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && count < MODS_MAX_FILES)
            {
                snprintf(names[count], MODS_NAME_MAX, "%s", fd.cFileName);
                ++count;
            }
        } while (FindNextFileA(h, &fd));
        FindClose(h);
    }
#else
    DIR* d = opendir(folder);
    if (d != NULL)
    {
        struct dirent* e;
        while ((e = readdir(d)) != NULL && count < MODS_MAX_FILES)
        {
            size_t len = strlen(e->d_name);
            if (len > 4 && strcmp(e->d_name + len - 4, ".lua") == 0)
            {
                snprintf(names[count], MODS_NAME_MAX, "%s", e->d_name);
                ++count;
            }
        }
        closedir(d);
    }
#endif

    qsort(names, (size_t)count, MODS_NAME_MAX, SortName);
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

    static char names[MODS_MAX_FILES][MODS_NAME_MAX];
    int count = ListLuaFiles(folder, names);
    if (count == 0)
    {
        OSReport("[mods] no scripts in %s\n", folder);
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

    for (int i = 0; i < count; ++i)
    {
        char full[1400];
        snprintf(full, sizeof full, "%s/%s", folder, names[i]);
        OSReport("[mods] running %s\n", names[i]);
        if (luaL_dofile(gL, full) != LUA_OK)
        {
            OSReport("[mods] ERROR in %s: %s\n", names[i], lua_tostring(gL, -1));
            lua_pop(gL, 1);
        }
    }
    OSReport("[mods] %d script(s) loaded\n", count);
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
