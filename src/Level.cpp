
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
    UserInterface = std::make_unique<SUi>();
}
Level::Level(const Level &l) : Level(l.Id, l.Name)
{
}
Level::Level(const Level &&l) : Level(l.Id, l.Name)
{
}
void Level::addObject(std::shared_ptr<IEntity> ie)
{
    ObjList.push_back(ie);
    ie->setName("def" + std::to_string(ObjList.size()));
    for(auto &d : ie->getDrawable())
    {
        DrawableComponents.push_back(d.lock());
    }
    if(ObjList.size() > 1)
    {
        int count = 0;
        for(auto o : ObjList)
        {
            auto body = o->getComponent<CPrimitiveQuad>("body").lock();
            if(o == ie)
                continue;
            if(body && ie->getComponent<CPrimitiveQuad>("body").lock())
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
//        ie->getBody()->setIndex(count);
        ie->getComponent<CPrimitiveQuad>("body").lock()->setIndex(count);
    }
}
std::shared_ptr<IEntity> Level::getObject(int index)
{
    if (!ObjList.empty())
    {
        return ObjList[index];
    }
    return nullptr;
}
std::vector<std::shared_ptr<IEntity>> &Level::getAllObjects()
{
    return ObjList;
}
size_t Level::getObjCount()
{
    return ObjList.size();
}

Level::~Level()
{
    DrawableComponents.clear();
    ObjList.clear();
    delete UserInterface->gui;
}
void Level::draw(sf::RenderWindow &window)
{
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
            [](std::shared_ptr<IEntity> t1, std::shared_ptr<IEntity> t2)
            {
                auto b1 = t1->getComponent<CPrimitiveQuad>("body").lock();
                auto b2 = t2->getComponent<CPrimitiveQuad>("body").lock();
                if(b1 && b2)
                {
                    return b1->getIndex() < b2->getIndex();
                }
                return false;
            });
    DrawableComponents.clear();
    for(auto o : ObjList)
    {
        for(auto &d : o->getDrawable())
        {
            DrawableComponents.push_back(d.lock());
        }
    }

}
void Level::loadGui(sf::RenderWindow &window)
{

}
void Level::DestroyEntity(int entityId)
{
    std::cout << "Destroyed id: " << entityId << std::endl;
    //ToDo: replace raw-pointer to smart pointers. Again
    ObjList.erase(std::remove(ObjList.begin(), ObjList.end(), getObjectById(entityId)), ObjList.end());
}
std::shared_ptr<IEntity> Level::getObjectById(int id)
{
    for(auto o : ObjList)
    {
        if (o->GetId() == id)
        {
            return o;
        }
    }
    return nullptr;
}
std::shared_ptr<IEntity> Level::getObjectByName(const std::string &N)
{
    for (auto o : ObjList)
    {
        if (o->getName() == N)
        {
            return o;
        }
    }
    return nullptr;
}
