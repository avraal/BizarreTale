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
    for (auto &o : obj)
    {
        toFile.write((char *) (o.get()), sizeof(MapEntity));
    }
    toFile.close();
    obj.clear();
}
void MapIO::LoadFromFIle(std::string fileName, std::vector<std::shared_ptr<MapEntity>> &obj)
{
    std::cout << "Preparing to read..." << std::endl;
    std::ifstream fromFile(fileName.c_str(), std::ios_base::in);
    if (!fromFile)
    {
        std::cerr << "[MapIO | LoadFromFile] File not found" << std::endl;
        return;
    }

    //obj.clear();
    MapEntity me;
    while (fromFile.read((char *) &me, sizeof(MapEntity)))
    {
//        obj.push_back(std::make_shared<MapEntity>(me));
        obj.push_back(std::make_shared<MapEntity>(me));
//        std::cout << "Added " << me.name << std::endl;
//        std::cout << "Position: " << me.getPosition().x << " : " << me.getPosition().y << std::endl;
//        std::cout << "Added " << obj.back()->name << std::endl;
//        std::cout << "Position: " << obj.back()->getPosition().x << " : " << obj.back()->getPosition().y << std::endl;
    }

    fromFile.close();
    std::cout << std::endl;

//    std::cout << "Value: " << obj.front()->_imagePath << std::endl;
//    std::cout << "Size: " << strlen(obj.front()->_imagePath) << std::endl;

    for (auto o : obj)
    {
        std::cout << o->name << std::endl;
        std::cout << "Position: " << o->getPosition().x << " : " << o->getPosition().y << std::endl;
    }
}
