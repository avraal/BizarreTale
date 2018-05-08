// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by andrew on 16.04.18.
//

#include <thread>
#include "MapIO.h"
void MapIO::SaveToFile(std::string fileName, std::list<std::shared_ptr<MapEntity>> obj)
{
    std::cout << "Preparing to write..." << std::endl;

    script.SaveToFile(fileName.c_str(), obj);
}
void MapIO::LoadFromFile(std::string fileName, std::list<std::shared_ptr<MapEntity>> &obj)
{
    std::cout << "Preparing to read..." << std::endl;

    obj.clear();

    script.LoadFromFile(fileName.c_str(), obj);
}
int MapIO::LuaSaveToFile(lua_State *)
{
    std::cout << "Writing..." << std::endl;
    return 0;
}
int MapIO::LuaLoadFromFile(lua_State *)
{
    std::cout << "Reading..." << std::endl;
    return 0;
}
