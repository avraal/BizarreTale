
// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by Andrew Volski on 10.07.18.
//
#include <algorithm>
#include "IEntity.hpp"
#include "../Level.hpp"
int IEntity::GetId() const
{
    return Id;
}

void IEntity::addComponent(std::shared_ptr<IComponent> component)
{
    //TODO: add checking on unique value
    Components.push_back(component);
}
IEntity::~IEntity()
{
}
IEntity::IEntity(int id)
{
    this->Id = id;
    this->body = nullptr;
    Position = {0.f, 0.f};
    Name = "def";
}
std::string IEntity::getName() const
{
    return Name;
}
void IEntity::setName(const std::string &name)
{
    this->Name = name;
}
void IEntity::setId(int id)
{
    this->Id = id;
}
std::shared_ptr<CPrimitiveQuad> IEntity::getBody()
{
    return body;
}
void IEntity::setPosition(float x, float y)
{
    if(body != nullptr)
    {
        body->setPosition(x, y);
        Position.x = x;
        Position.y = y;
    }
}
void IEntity::setPosition(const sf::Vector2f &position)
{
    if(body != nullptr)
    {
        body->setPosition(position);
        this->Position = position;
    }
}
sf::Vector2f IEntity::getPosition() const
{
    return Position;
}
