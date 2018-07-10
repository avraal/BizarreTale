
// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by Andrew Volski on 10.07.18.
//

#include "Level.hpp"
Level::Level(int id, const std::string &Name)
{
    this->Id = id;
    this->Name = Name;
}
Level::Level(const Level &l) : Level(l.Id, l.Name)
{
}
Level::Level(const Level &&l) : Level(l.Id, l.Name)
{
}
void Level::addObject(std::shared_ptr<TileEntity> te)
{
    ObjList.push_back(te);
}
std::shared_ptr<TileEntity> Level::getObject(int index)
{
    if(!ObjList.empty())
    {
        return ObjList[index];
    }
    return nullptr;
}
std::vector<std::shared_ptr<TileEntity>> &Level::getAllObjects()
{
    return ObjList;
}
size_t Level::getObjCount()
{
    return ObjList.size();
}
Level::~Level()
{

}
