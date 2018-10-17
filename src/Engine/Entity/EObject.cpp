
// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by Andrew Volski on 12.07.18.
//

#include "EObject.hpp"
#include "../Systems/Managers/ComponentManager.hpp"

EObject::~EObject()
{
}
EObject::EObject(us_int id, const std::string &name) : IEntity(id, name)
{
    body = nullptr;
    transform = nullptr;
}
CDrawable *EObject::getBody() const
{
    return body;
}
CTransform *EObject::getTransform() const
{
    return transform;
}
void EObject::setPosition(const sf::Vector2f &pos)
{
    transform->setPosition(pos);
    body->setPosition(pos);
}
void EObject::setPosition(const sf::Vector2i &pos)
{
    setPosition(sf::Vector2f(pos));
}
