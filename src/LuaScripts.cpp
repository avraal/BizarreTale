//
// Created by andrew on 23.04.18.
//

#include "LuaScripts.h"
void LuaScripts::Create()
{
    lua_state = luaL_newstate();

    static const luaL_Reg lualibs[] =
            {
                    {"base", luaopen_base},
                    {"io",   luaopen_io},
                    {"string", luaopen_string},
                    {NULL, NULL}
            };

    for (const luaL_Reg *lib = lualibs; lib->func != NULL; lib++)
    {
        luaL_requiref(lua_state, lib->name, lib->func, 1);
        lua_settop(lua_state, 0);
    }
}
void LuaScripts::Close()
{
    lua_close(lua_state);
}
int LuaScripts::DoFile(char *ScriptFileName)
{
    luaL_dofile(lua_state, ScriptFileName);
    return lua_tointeger(lua_state, lua_gettop(lua_state));
}

template<>
void LuaScripts::RegisterConstant<lua_CFunction>(lua_CFunction value, char *constName)
{
    lua_pushcfunction(lua_state, value);
    lua_setglobal(lua_state, constName);
}
template<>
void LuaScripts::Push<char*>(char *value)
{
    lua_pushstring(lua_state, value);
}
template<>
void LuaScripts::Push<const char*>(const char* value)
{
    lua_pushstring(lua_state, value);
}
template<>
void LuaScripts::Push<bool>(bool value)
{
    lua_pushboolean(lua_state, value);
}
template<>
void LuaScripts::Push<double>(double value)
{
    lua_pushnumber(lua_state, value);
}
template <>
void LuaScripts::Push<int>(int value)
{
    lua_pushinteger(lua_state, value);
}

void LuaScripts::SaveToFile(MapEntity *value, const char *fileName)
{
    lua_getglobal(lua_state, "SaveMapEntityToFile");
    Push<const char*>(fileName);
    Push<char*>(value->name);
    Push<char*>(value->getImagePath());
    Push<double>(value->getPosition().x);
    Push<double>(value->getPosition().y);
    lua_call(lua_state, 5, 0);
    lua_pop(lua_state, 1);
}