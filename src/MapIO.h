// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by andrew on 16.04.18.
//

#ifndef BIZARRETALE_MAPIO_H
#define BIZARRETALE_MAPIO_H

#include <fstream>
#include <memory>
#include <cstring>
#include <list>
#include "TileEntity.h"
#include "LuaScripts.h"
#include "json.hpp"

using json = nlohmann::json;

class MapIO
{
private:
    LuaScripts script;

    MapIO()
    {
        script.Create();
        script.RegisterConstant<lua_CFunction>(reinterpret_cast<lua_CFunction>(&MapIO::LuaSaveToFile),
                                               "SaveMapEntityToFile");
        script.RegisterConstant<lua_CFunction>(reinterpret_cast<lua_CFunction>(&MapIO::LuaLoadFromFile),
                                               "LoadMapEntityFromFile");
        script.DoFile("Res/Lua/EntityIO.lua");
    }
    ~MapIO()
    {
        script.Close();
    }
    int LuaSaveToFile(lua_State *);
    int LuaLoadFromFile(lua_State *);
public:
    MapIO(MapIO const &) = delete;
    MapIO &operator=(MapIO const &) = delete;
    static MapIO &Instance()
    {
        static MapIO mio;
        return mio;
    }

    void SaveToFile(std::string fileName, std::list<std::shared_ptr<TileEntity>> obj);
    void LoadFromFile(std::string fileName, std::list<std::shared_ptr<TileEntity>> &obj);
};

#endif //BIZARRETALE_MAPIO_H
