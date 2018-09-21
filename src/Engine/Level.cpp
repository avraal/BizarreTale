
// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by Andrew Volski on 10.07.18.
//

#include <SFML/Window/Event.hpp>
#include "Level.hpp"
#include "Entity/IEntity.hpp"

us_int Level::currentId = 0;

Level::Level(const std::string &Name)
{
    this->Id = Level::getNextId();
    this->Name = Name;
    backGroundColor = sf::Color::Black;
    UserInterface = std::make_unique<UIWrapper>();
    objDetails = std::make_unique<ObjectsDetails>();
}
void Level::addObject(std::shared_ptr<IEntity> ie)
{
    ObjList.push_back(ie);
    objDetails->objCount++;
    ie->setName("def" + std::to_string(ObjList.size()));
    for(auto d : ie->getDrawable())
    {
        DrawableComponents.push_back(d);
        objDetails->drawableCount++;
    }
    if(ObjList.size() > 1)
    {
        us_int count = 0;
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
std::shared_ptr<IEntity> Level::getObject(us_int index)
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
us_int Level::getObjCount()
{
    return ObjList.size();
}

Level::~Level()
{
    DrawableComponents.clear();
    ObjList.clear();
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
bool Level::DestroyEntity(us_int entityId)
{
    us_int beforeObjCount = ObjList.size();
    us_int beforeDrawCount = DrawableComponents.size();
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
            objDetails->drawableCount--;
        } else
        {
            ++it;
        }
    }

    ObjList.erase(std::remove(ObjList.begin(), ObjList.end(), getObjectById(entityId)), ObjList.end());
    objDetails->objCount--;
    return beforeObjCount != ObjList.size() && beforeDrawCount != DrawableComponents.size();
}
std::shared_ptr<IEntity> Level::getObjectById(us_int id)
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
us_int Level::getNextId()
{
    return Level::currentId++;
}
bool Level::findAllFiles(std::vector<std::string> &Container, std::vector<std::string> FileFormats)
{
    bool result = false;
    DIR *dir;
    dirent *directory;
    if (FileFormats.empty())
    {
        FileFormats.emplace_back(".*");
    }
    std::cout << ImageDirectory << std::endl;
    if ((dir = opendir(ImageDirectory.c_str())) != nullptr)
    {
        while ((directory = readdir(dir)) != nullptr)
        {
            char *last = strrchr(directory->d_name, '.');
            if (last != nullptr)
            {
                for (const auto &f : FileFormats)
                {
                    if (strcmp(last, f.c_str()) == 0)
                    {
                        Container.push_back(ImageDirectory + directory->d_name);
                        result = true;
                    }
                }
            }
        }
        closedir(dir);
    } else
    {
        std::cerr << "Can't open a dir" << std::endl;
        result = false;
    }
    return result;
}

