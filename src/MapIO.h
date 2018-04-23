//
// Created by andrew on 16.04.18.
//

#ifndef BIZARRETALE_MAPIO_H
#define BIZARRETALE_MAPIO_H

#include <fstream>
#include <memory>
#include <cstring>
#include "MapEntity.h"
#include "LuaScripts.h"

class MapIO
{
private:
    LuaScripts script;

    MapIO()
    {
        script.Create();
        script.RegisterConstant<lua_CFunction>(reinterpret_cast<lua_CFunction>(&MapIO::LuaSaveToFile), "SaveMapEntityToFile");
        script.DoFile("EntityIO.lua");
    }
    ~MapIO()
    {
        script.Close();
    }
public:
    MapIO(MapIO const &) = delete;
    MapIO &operator=(MapIO const &) = delete;
    static MapIO &Instance()
    {
        static MapIO mio;
        return mio;
    }
    int LuaSaveToFile(lua_State*);
    void SaveToFile(std::string fileName, std::vector<std::shared_ptr<MapEntity>> &obj,
                    std::vector<std::shared_ptr<MapEntity>> tiles);
    void LoadFromFIle(std::string fileName, std::vector<std::shared_ptr<MapEntity>> &obj);
};

#endif //BIZARRETALE_MAPIO_H
