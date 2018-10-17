
// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by Andrew Volski on 10.07.18.
//

#include <SFML/Window/Event.hpp>
#include "Level.hpp"
#include "Systems/Managers/EntityManager.hpp"
#include "Systems/Managers/ComponentManager.hpp"
#include "Entity/EObject.hpp"

us_int Level::currentId = 0;

Level::Level(const std::string &Name)
{
    this->Id = Level::getNextId();
    this->Name = Name;
    ImageDirectory = "";
    ImagesFormats.push_back(".png");
    ImagesFormats.push_back(".jpg");
    backgroundColor = sf::Color::Black;
    UserInterface = std::make_unique<UIWrapper>();
    objDetails = std::make_unique<ObjectsDetails>();

    EntityManager::Register<EObject>();
    ComponentManager::Register<CDrawable>();
    ComponentManager::Register<CTransform>();
}
void Level::addObject(us_int entityId)
{
    ObjectIds.push_back(entityId);
    objDetails->objCount++;
    EObject *target = static_cast<EObject *>(EntityManager::getEntity(entityId));
    //setName
    for (auto d : target->ComponentsId)
    {
        DrawableComponentIds.push_back(d);
        CDrawable *c = dynamic_cast<CDrawable *>(ComponentManager::getComponent(d));
        if (c)
        {
            DrawableComponents.push_back(c);
        }
    }
    objDetails->drawableCount += target->ComponentsId.size();

    if (ObjectIds.size() > 1)
    {
        us_int count = 0;
        for (auto o : ObjectIds)
        {
            if (o == target->getId())
            {
                continue;
            }
            if (target->getBody())
            {
                EObject *e = static_cast<EObject *>(EntityManager::getEntity(o));
                if (e->getBody())
                {
                    if (target->getTransform()->getPosition() == e->getTransform()->getPosition())
                    {
                        count++;
                    }
                }
            }
        }
        target->getBody()->setIndex(count);
    }

}

us_int Level::getObjCount()
{
    return ObjectIds.size();
}

Level::~Level()
{
    for (auto id : ObjectIds)
    {
        EntityManager::Destroy(id);
    }
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
//    std::sort(DrawableComponents.begin(), DrawableComponents.end(),
//            [](std::shared_ptr<CPrimitiveQuad> c1, std::shared_ptr<CPrimitiveQuad> c2)
//            {
//                return c1->getIndex() < c2->getIndex();
//            });

    std::sort(ObjectIds.begin(), ObjectIds.end(),
            [](us_int o1, us_int o2)
            {
                CDrawable *b1 = static_cast<EObject *>(EntityManager::getEntity(o1))->getBody();
                CDrawable *b2 = static_cast<EObject *>(EntityManager::getEntity(o2))->getBody();
                if (b1 && b2)
                {
                    return b1->getIndex() < b2->getIndex();
                }
                return false;
            });
}
void Level::loadGui(sf::RenderWindow &window)
{

}

bool Level::prepareLevel(sf::RenderWindow &window)
{
    if (!findAllFiles(PathToImages, ImagesFormats))
    {
        return false;
    }
    initGui(window);
    return true;
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

