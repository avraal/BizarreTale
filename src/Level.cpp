
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
    UserInterface = new SUi();
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
    for(auto &d : ie->getDrawable())
    {
        DrawableComponents.push_back(d);
    }
    if(ObjList.size() > 1)
    {
        int count = 0;
        for(auto o : ObjList)
        {
            if(o == ie)
                continue;
            if(o->getBody() != nullptr && ie->getBody() != nullptr)
            {
                if(o->getPosition() == ie->getPosition())
                {
                    count++;
                }
            }
            else
            {
                return;
            }
        }
        ie->getBody()->setIndex(count);
    }
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
    delete UserInterface->gui;
    delete UserInterface;
}
void Level::draw(sf::RenderWindow &window)
{
    float currentTime = clock.restart().asSeconds();
    float fps = 1.f / currentTime;

    for(auto d : DrawableComponents)
    {
        window.draw(*d);
    }

    UserInterface->Execute();
}
std::string Level::getName() const
{
    return Name;
}
void Level::initGui(sf::RenderWindow &window)
{
    UserInterface->gui = new tgui::Gui(window);
    loadGui(window);
}
void Level::sortedObjectsByIndex()
{
    std::sort(ObjList.begin(), ObjList.end(),
            [](IEntity *t1, IEntity *t2)
            {
                if(t1->getBody() != nullptr && t2->getBody() != nullptr)
                {
                    return t1->getBody()->getIndex() < t2->getBody()->getIndex();
                }
                return false;
            });
    DrawableComponents.clear();
    for(auto o : ObjList)
    {
        for(auto &d : o->getDrawable())
        {
            DrawableComponents.push_back(d);
        }
    }

}
void Level::loadGui(sf::RenderWindow &window)
{

}
