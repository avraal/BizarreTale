// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by andrew on 23.04.18.
//

#include "LuaScripts.h"

template<>
void LuaScripts::RegisterConstant<lua_CFunction>(lua_CFunction value, char *constName)
{
    lua_pushcfunction(lua_state, value);
    lua_setglobal(lua_state, constName);
}
template<>
void LuaScripts::Push<char *>(char *value)
{
    lua_pushstring(lua_state, value);
}
template<>
void LuaScripts::Push<const char *>(const char *value)
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
template<>
void LuaScripts::Push<int>(int value)
{
    lua_pushinteger(lua_state, value);
}

void LuaScripts::Create()
{
    lua_state = luaL_newstate();

    static const luaL_Reg lualibs[] =
            {
                    {"base",   luaopen_base},
                    {"io",     luaopen_io},
                    {"string", luaopen_string},
                    {NULL, NULL}
            };

    for (const luaL_Reg *lib = lualibs; lib->func != NULL; lib++)
    {
        luaL_requiref(lua_state, lib->name, lib->func, 1);
        lua_settop(lua_state, 0);
    }

    RegisterConstant<lua_CFunction>(reinterpret_cast<lua_CFunction>(&LuaScripts::getTableSize), "getTableSize");
}
void LuaScripts::Close()
{
    try
    {
        lua_close(lua_state);
    }
    catch (std::exception &ex)
    {
        std::cerr << ex.what() << std::endl;
    }
}
int LuaScripts::DoFile(char *ScriptFileName)
{
    luaL_dofile(lua_state, ScriptFileName);
    return lua_tointeger(lua_state, lua_gettop(lua_state));
}

void LuaScripts::SaveToFile(const char *fileName, std::vector<std::shared_ptr<MapEntity>> obj)
{
    lua_getglobal(lua_state, "SaveMapEntityToFile");

    Push<const char *>(fileName);

    lua_newtable(lua_state);
    for (int i = 0; i < obj.size(); i++)
    {
        Push<const char *>(std::to_string(i).c_str());
        lua_newtable(lua_state);
        Push<char *>("name");
        Push<char *>(obj[i]->name);
        lua_settable(lua_state, -3);
        Push<char *>("imagePath");
        Push<char *>(obj[i]->getImagePath());
        lua_settable(lua_state, -3);
        Push<char *>("x");
        Push<double>(obj[i]->getPosition().x);
        lua_settable(lua_state, -3);
        Push<char *>("y");
        Push<double>(obj[i]->getPosition().y);
        lua_settable(lua_state, -3);
        lua_settable(lua_state, -3);
    }

    lua_call(lua_state, 2, 0);
    lua_pop(lua_state, 0);
}
void LuaScripts::LoadFromFile(const char *fileName, std::vector<std::shared_ptr<MapEntity>> &obj)
{
    int size = getTableSize(fileName);

    lua_getglobal(lua_state, "LoadMapEntityFromFile");
    Push<const char *>(fileName);
    lua_call(lua_state, 1, 1);
    lua_getfield(lua_state, 1, "u");

    for (int i = 0; i < size; i++)
    {
        lua_getfield(lua_state, 1, std::to_string(i).c_str());
        lua_getfield(lua_state, -1, "imagePath");
        std::string imagePath = lua_tostring(lua_state, -1);
//        std::cout << "Path: " << lua_tostring(lua_state, -1) << std::endl;
        lua_getfield(lua_state, -2, "name");
//        std::cout << "Name: " << lua_tostring(lua_state, -1) << std::endl;
        lua_getfield(lua_state, -3, "x");
        float x = lua_tonumber(lua_state, -1);
//        std::cout << "X: " << lua_tonumber(lua_state, -1) << std::endl;
        lua_getfield(lua_state, -4, "y");
        float y = lua_tonumber(lua_state, -1);
//        std::cout << "Y: " << lua_tonumber(lua_state, -1) << std::endl;
        obj.push_back(std::move(std::shared_ptr<MapEntity>(new MapEntity(imagePath.c_str(), {x, y}))));
    }

    lua_pop(lua_state, 1);
}
int LuaScripts::getTableSize(const char *fileName)
{
    lua_getglobal(lua_state, "getTableSize");
    Push<const char *>(fileName);
    lua_call(lua_state, 1, 1);
    lua_getfield(lua_state, 0, "c");
    int res = lua_tointeger(lua_state, 1);
    lua_pop(lua_state, 2);
    return res;
}
int LuaScripts::LuaGetTableSize(lua_State *)
{
    return 0;
}
