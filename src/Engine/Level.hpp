
// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by Andrew Volski on 10.07.18.
//

#ifndef DEMIURGE_LEVEL_HPP
#define DEMIURGE_LEVEL_HPP

#include <string>
#include <string.h>
#include <vector>
#include <memory>
#include <algorithm>
#include <dirent.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include <TGUI/Widgets/Label.hpp>
#include <TGUI/Widgets/Panel.hpp>
#include <TGUI/Widgets/ScrollablePanel.hpp>
#include <forward_list>
#include "Components/CPrimitiveQuad.hpp"
#include "Systems/UIWrapper.hpp"

class IEntity;
class EObject;

struct ObjectsDetails
{
    ObjectsDetails() : objReferenceCount{0}, drawableReferenceCount{0}, objCount{0}, drawableCount{0} {}
    us_int objReferenceCount;
    us_int drawableReferenceCount;
    us_int objCount;
    us_int drawableCount;
};

class Level
{
protected:
    size_t Id;
    std::string Name;
    std::vector<std::shared_ptr<IEntity>> ObjList;
    std::vector<std::shared_ptr<CPrimitiveQuad>> DrawableComponents;
    std::vector<tgui::Widget::Ptr> guiContainer;
    sf::Clock clock;
    sf::View *MainCamera;
    sf::Color backGroundColor;
    void virtual loadGui(sf::RenderWindow &window);
    void initGui(sf::RenderWindow &window);
    bool findAllFiles(std::vector<std::string> &Container, std::vector<std::string> FileFormats);
    std::unique_ptr<UIWrapper> UserInterface;

    static us_int currentId;
    static us_int getNextId();
public:
    Level() = delete;
    Level(const std::string &Name);
    Level(const Level&)             = delete;
    Level(const Level&&)            = delete;
    Level&operator=(const Level&)   = delete;
    ~Level();
    virtual void draw(sf::RenderWindow &window);

    bool DestroyEntity(us_int entityId);
    virtual bool prepareLevel(sf::RenderWindow &window);
    void addObject(std::shared_ptr<IEntity> ie);
    void sortedObjectsByIndex();
    void setCamera(sf::View &camera);
    virtual void MouseCallbacks(sf::RenderWindow &window, sf::Event &event) = 0;
    virtual void KeyBoardCallbacks(sf::RenderWindow &window, sf::Event &event) = 0;
    virtual void HandleGUIEvent(sf::Event &event);
    us_int getObjCount();
    std::shared_ptr<IEntity> getObject(us_int index);
    std::shared_ptr<IEntity> getObjectById(us_int id);
    std::shared_ptr<IEntity> getObjectByName(const std::string &Name);
    std::unique_ptr<ObjectsDetails> objDetails;
    std::vector<std::shared_ptr<IEntity>> &getAllObjects();
    virtual std::string getName() const;
    std::string ImageDirectory;
    float fps;

};

#endif //DEMIURGE_LEVEL_HPP
