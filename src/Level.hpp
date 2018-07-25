
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
#include <SFML/Graphics/RenderWindow.hpp>
#include "CPrimitiveQuad.hpp"

class IEntity;
class EObject;
class Level final
{
private:
    int Id;
    std::string Name;
    std::vector<IEntity*> ObjList;
    std::vector<CPrimitiveQuad*> DrawableComponents;
    sf::Clock clock;
    void sortObjects();
public:
    Level() = delete;
    Level(int id, const std::string &Name);
    Level(const Level&);
    Level(const Level&&);
    ~Level();

    void draw(sf::RenderWindow &window);
    void CreateObject(EObject *ie);

    void addObject(IEntity *ie);
    size_t getObjCount();
    IEntity *getObject(int index);
    std::vector<IEntity*> &getAllObjects();
};

#endif //BIZARRETALE_LEVEL_HPP
