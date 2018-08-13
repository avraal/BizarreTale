
// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by Andrew Volski on 12.07.18.
//

#include "EObject.hpp"
#include "../CPrimitiveQuad.hpp"
#include "../Level.hpp"
#include "../CTile.h"
#include "../Util/IDGenerator.hpp"

EObject::~EObject()
{
//    delete body;
}
EObject::EObject(const std::string &ImagePath)
{
    std::cout << "EO default ctor" << std::endl;
    if (!ImagePath.empty())
    {
//        body = new CTile(this, IDGenerator::getId(), "body", ImagePath, getPosition());
//        auto body = std::make_shared<CTile>()
    }
}
EObject::EObject(EObject &&eo)
{
    std::cout << "EO move ctor" << std::endl;
    body = eo.body;
    Position = eo.Position;
    Components.clear();
    std::copy(eo.Components.begin(), eo.Components.end(), std::back_inserter(Components));
    Name = eo.Name;
    Id = IEntity::getNextId();
}
EObject::EObject(const EObject &rhs) : IEntity(rhs)
{
    std::cout << "EO copy ctor" << std::endl;
    this->body = rhs.body;
}
EObject &EObject::operator=(const EObject &rhs)
{
    IEntity::operator=(rhs);
    this->body = rhs.body;
    return *this;
}
void EObject::setPosition(float x, float y)
{
    if (body)
    {
        body->setPosition(x, y);
        Position.x = x;
        Position.y = y;
    }
}
void EObject::setPosition(const sf::Vector2f &position)
{
    if (body)
    {
        body->setPosition(position);
        this->Position = position;
    }
}
std::shared_ptr<CPrimitiveQuad> EObject::getBody()
{
    return getComponent<CPrimitiveQuad>("body").lock();
}
