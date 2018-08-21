
// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by Andrew Volski on 10.07.18.
//

#include <SFML/Window/Event.hpp>
#include "Level.hpp"
#include "Entity/IEntity.hpp"
Level::Level(int id, const std::string &Name)
{
    this->Id = id;
    this->Name = Name;
    backGroundColor = sf::Color::Black;
    UserInterface = std::make_unique<UIWrapper>();
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
    for(auto d : ie->getDrawable())
    {
        DrawableComponents.push_back(d);
    }
    if(ObjList.size() > 1)
    {
        int count = 0;
        for(auto o : ObjList)
        {
            auto body = o->getComponent<CPrimitiveQuad>("body");
            if(o == ie)
                continue;
            if(body && ie->getComponent<CPrimitiveQuad>("body"))
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
        ie->getComponent<CPrimitiveQuad>("body")->setIndex(count);
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
//    delete UserInterface->gui;
}
void Level::draw(sf::RenderWindow &window)
{
    float currentTime = clock.restart().asSeconds();
    fps = 1.f / currentTime;
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
//    UserInterface->gui = new tgui::Gui(window);
    UserInterface->gui = std::make_unique<tgui::Gui>(window);
    loadGui(window);
}
void Level::sortedObjectsByIndex()
{
    std::sort(ObjList.begin(), ObjList.end(),
            [](std::shared_ptr<IEntity> t1, std::shared_ptr<IEntity> t2)
            {
                auto b1 = t1->getComponent<CPrimitiveQuad>("body");
                auto b2 = t2->getComponent<CPrimitiveQuad>("body");
                if (b1 && b2)
                {
                    return b1->getIndex() < b2->getIndex();
                }
                return false;
            });
    std::sort(DrawableComponents.begin(), DrawableComponents.end(),
            [](std::shared_ptr<CPrimitiveQuad> c1, std::shared_ptr<CPrimitiveQuad> c2)
            {
                return c1->getIndex() < c2->getIndex();
            });
}
void Level::loadGui(sf::RenderWindow &window)
{

}
bool Level::DestroyEntity(int entityId)
{
    std::size_t beforeObjCount = ObjList.size();
    std::size_t beforeDrawCount = DrawableComponents.size();
    auto target = getObjectById(entityId);
    if (!target)
    {
        return false;
    }
    std::cout << target->getComponent("body").use_count() << std::endl;
    target->removeComponents();

    for (auto it = DrawableComponents.begin(); it != DrawableComponents.end(); )
    {
        if ((*it)->getEntity() == target)
        {
            (*it)->release();
            it = DrawableComponents.erase(it);
        } else
        {
            ++it;
        }
    }

    ObjList.erase(std::remove(ObjList.begin(), ObjList.end(), getObjectById(entityId)), ObjList.end());

    return beforeObjCount != ObjList.size() && beforeDrawCount != DrawableComponents.size();
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
bool Level::prepareLevel(sf::RenderWindow &window)
{
    bool result = true;
    initGui(window);
    return result;
}
void Level::HandleGUIEvent(sf::Event &event)
{
    UserInterface->gui->handleEvent(event);
}

void Level::setCamera(sf::View &camera)
{
    this->MainCamera = &camera;
}
