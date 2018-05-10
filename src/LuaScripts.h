// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by andrew on 23.04.18.
//

#ifndef BIZARRETALE_LUASCRIPTS_H
#define BIZARRETALE_LUASCRIPTS_H

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include "TileEntity.h"
#include <iostream>
#include <list>
#include <memory>

class LuaScripts
{
private:
    lua_State *lua_state;

    int LuaGetTableSize(lua_State *);

public:
    void Create();
    void Close();
    int DoFile(const char *ScriptFileName);

    template <class T>
            void Push(T value);

    template <class T>
            void RegisterConstant(T value, const char *constName);

    void SaveToFile   (const char *fileName, std::list<std::shared_ptr<TileEntity>> obj);
    void LoadFromFile (const char *fileName, std::list<std::shared_ptr<TileEntity>> &obj);
    int getTableSize  (const char *fileName);
};

#endif //BIZARRETALE_LUASCRIPTS_H
