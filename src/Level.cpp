
// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by Andrew Volski on 10.07.18.
//

#include <SFML/Window/Event.hpp>
#include "Level.hpp"
#include "Abstract/IEntity.hpp"
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
void Level::addObject(IEntity *ie)
{
    ObjList.push_back(ie);
    ie->setId(ObjList.size());
    ie->setName("def" + std::to_string(ObjList.size()));
}
IEntity *Level::getObject(int index)
{
    if (!ObjList.empty())
    {
        return ObjList[index];
    }
    return nullptr;
}
std::vector<IEntity*> &Level::getAllObjects()
{
    return ObjList;
}
size_t Level::getObjCount()
{
    return ObjList.size();
}

Level::~Level()
{
    for(auto d : DrawableComponents)
    {
        delete d;
    }
    DrawableComponents.clear();
    for(auto o : ObjList)
    {
        delete o;
    }
    ObjList.clear();
}
void Level::draw(sf::RenderWindow &window)
{
    for (auto o : ObjList)
    {
        for (auto d : o->getDrawable())
        {
            window.draw(*d);
        }
    }
}
void Level::CreateObject(EObject *ie)
{

}
