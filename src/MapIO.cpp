// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by andrew on 16.04.18.
//

#include <thread>
#include <deque>
#include "MapIO.h"
void MapIO::SaveToFile(std::string fileName, std::list<std::shared_ptr<TileEntity>> obj)
{
    std::cout << "Preparing to write..." << std::endl;

    json j;

    for(auto o : obj)
    {
        j[o->Name] = {{"index", o->getIndex()}, {"position", {o->getPosition().x, o->getPosition().y}},
                      {"size", {o->getSize().x*TILE_SIZE_DEFAULT, o->getSize().y*TILE_SIZE_DEFAULT}}, {"image", o->GetImagePath()}};
    }

    std::string result = j.dump();
    std::ofstream to_file(fileName, std::ios_base::trunc);
    if(!to_file)
    {
        //error
        return;
    }

    to_file << result;
    to_file.close();

//    script.SaveToFile(fileName.c_str(), obj);
}
void MapIO::LoadFromFile(std::string fileName, std::list<std::shared_ptr<TileEntity>> &obj)
{
    std::cout << "Preparing to read..." << std::endl;
    obj.clear();
    std::ifstream from_file(fileName, std::ios_base::in);
    if(!from_file)
    {
        //error
        return;
    }
    std::string response;
    while(!from_file.eof())
    {
        from_file >> response;
    }

    from_file.close();
    json j1 = json::parse(response);
    for(json::iterator it = j1.begin(); it != j1.end(); ++it)
    {
        std::string name = it.key();
        json j2 = it.value();
        std::string imagePath = j2["image"];
        int index = j2["index"];
        json j_pos = j2["position"];
        float posX = j_pos[0];
        float posY = j_pos[1];
        json j_size = j2["size"];
        float sizeX = j_size[0];
        float sizeY = j_size[1];

        obj.push_back(std::move(std::shared_ptr<TileEntity>(new TileEntity(name, imagePath, {posX, posY}, index))));
        obj.back()->setSize({sizeX, sizeY});
    }
}
