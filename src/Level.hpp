
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
#include "CPrimitiveQuad.hpp"
#include "Systems/SUi.hpp"

class IEntity;
class EObject;
class Level final
{
private:
    int Id;
    std::string Name;
    std::vector<std::shared_ptr<IEntity>> ObjList;
    std::vector<std::shared_ptr<CPrimitiveQuad>> DrawableComponents;
    std::vector<tgui::Widget::Ptr> guiContainer;
    sf::Clock clock;
    void sortObjects();
    void loadGui(sf::RenderWindow &window);
    std::unique_ptr<SUi> UserInterface;
public:

    Level() = delete;
    Level(int id, const std::string &Name);
    Level(const Level&);
    Level(const Level&&);
    ~Level();
    void draw(sf::RenderWindow &window);

    void DestroyEntity(int entityId);
    void addObject(std::shared_ptr<IEntity> ie);
    void initGui(sf::RenderWindow &window);
    void sortedObjectsByIndex();
    size_t getObjCount();
    std::shared_ptr<IEntity> getObject(int index);
    std::shared_ptr<IEntity> getObjectById(int id);
    std::shared_ptr<IEntity> getObjectByName(const std::string &Name);
    std::vector<std::shared_ptr<IEntity>> &getAllObjects();
    std::string getName() const;
};

#endif //BIZARRETALE_LEVEL_HPP
