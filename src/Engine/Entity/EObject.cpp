
// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by Andrew Volski on 12.07.18.
//

#include "EObject.hpp"
#include "../Components/CPrimitiveQuad.hpp"
#include "../Level.hpp"
#include "../Components/CTile.h"
#include "../Util/IDGenerator.hpp"

EObject::~EObject()
{
}
EObject::EObject()
{
}
EObject::EObject(EObject &&eo)
{
    std::cout << "EO move ctor" << std::endl;
    Position = eo.Position;
    Components.clear();
    std::copy(eo.Components.begin(), eo.Components.end(), std::back_inserter(Components));
    Name = eo.Name;
    Id = IEntity::getNextId();
}
EObject::EObject(const EObject &rhs) : IEntity(rhs)
{
    std::cout << "EO copy ctor" << std::endl;
}
EObject &EObject::operator=(const EObject &rhs)
{
    IEntity::operator=(rhs);
    return *this;
}
void EObject::setPosition(float x, float y)
{
    setPosition({x, y});
}
void EObject::setPosition(const sf::Vector2f &position)
{
    this->Position = position;
    for (auto c : getDrawable())
    {
        c->setPosition(position);
    }
}