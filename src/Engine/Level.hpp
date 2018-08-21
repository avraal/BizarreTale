
// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by Andrew Volski on 10.07.18.
//

#ifndef BIZARRETALE_LEVEL_HPP
#define BIZARRETALE_LEVEL_HPP

#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <SFML/Graphics/RenderWindow.hpp>
#include <TGUI/Widgets/Label.hpp>
#include <TGUI/Widgets/Panel.hpp>
#include <TGUI/Widgets/ScrollablePanel.hpp>
#include <forward_list>
#include "Components/CPrimitiveQuad.hpp"
#include "Systems/UIWrapper.hpp"

class IEntity;
class EObject;
class Level
{
protected:
    int Id;
    std::string Name;
    std::vector<std::shared_ptr<IEntity>> ObjList;
    std::vector<std::shared_ptr<CPrimitiveQuad>> DrawableComponents;
    std::vector<tgui::Widget::Ptr> guiContainer;
    sf::Clock clock;
    sf::View *MainCamera;
    sf::Color backGroundColor;
    void virtual loadGui(sf::RenderWindow &window);
    void initGui(sf::RenderWindow &window);
    std::unique_ptr<UIWrapper> UserInterface;
public:
    Level() = delete;
    Level(int id, const std::string &Name);
    Level(const Level&);
    Level(const Level&&);
    ~Level();
    virtual void draw(sf::RenderWindow &window);

    bool DestroyEntity(int entityId);
    void addObject(std::shared_ptr<IEntity> ie);
    virtual bool prepareLevel(sf::RenderWindow &window);
    void sortedObjectsByIndex();
    void setCamera(sf::View &camera);
    void virtual MouseCallbacks(sf::RenderWindow &window, sf::Event &event) = 0;
    void virtual KeyBoardCallbacks(sf::RenderWindow &window, sf::Event &event) = 0;
    void HandleGUIEvent(sf::Event &event);
    size_t getObjCount();
    std::shared_ptr<IEntity> getObject(int index);
    std::shared_ptr<IEntity> getObjectById(int id);
    std::shared_ptr<IEntity> getObjectByName(const std::string &Name);
    std::vector<std::shared_ptr<IEntity>> &getAllObjects();
    std::string getName() const;
    std::string ImageDirectory;
    float fps;

};

#endif //BIZARRETALE_LEVEL_HPP
