//
// Created by andrew on 16.04.18.
//

#include "MapIO.h"
void MapIO::SaveToFile(std::string fileName, std::vector<std::shared_ptr<MapEntity>> &obj,
                       std::vector<std::shared_ptr<MapEntity>> tiles)
{
    std::cout << "Preparing to write..." << std::endl;
    std::ofstream toFile(fileName.c_str(), std::ios_base::trunc);
    if (!toFile)
    {
        std::cerr << "[MapIO | SaveToFile] File not found" << std::endl;
        return;
    }
    for (auto o : obj)
    {
        toFile.write((char *) &o, sizeof(o));
    }
    toFile.close();
}
void MapIO::LoadFromFIle(std::string fileName)
{
    std::vector<std::shared_ptr<MapEntity>> e;
    std::cout << "Preparing to read..." << std::endl;
    std::ifstream fromFile(fileName.c_str(), std::ios_base::in);
    if (!fromFile)
    {
        std::cerr << "[MapIO | LoadFromFile] File not found" << std::endl;
        return;
    }

    std::shared_ptr<MapEntity> me;
    while (fromFile.read((char *) &me, sizeof(me)))
    {
        e.push_back(me);
        std::cout << "Added " << me->name << std::endl;
        std::cout << "Position: " << me->getPosition().x << " : " << me->getPosition().y << std::endl;
    }

    fromFile.close();

    std::cout << std::endl;

    for (auto o : e)
    {
        std::cout << o->name << std::endl;
        std::cout << "Position: " << me->getPosition().x << " : " << me->getPosition().y << std::endl;
    }
}
