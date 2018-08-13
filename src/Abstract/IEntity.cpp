
// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by Andrew Volski on 10.07.18.
//
#include <algorithm>
#include "IEntity.hpp"
#include "../Level.hpp"

int IEntity::currentId = 0;

IEntity::IEntity()
{
    Id = IEntity::getNexId();
    body = nullptr;
    Position = {.0f, .0f};
    Name = "def";
}

int IEntity::GetId() const noexcept
{
    return Id;
}

void IEntity::addComponent(IComponent *component)
{
    Components.push_back(component);
}
IEntity::~IEntity()
{
    for (auto c : Components)
    {
        delete c;
    }
    Components.clear();
}

std::string IEntity::getName() const noexcept
{
    return Name;
}
void IEntity::setName(const std::string &name) noexcept
{
    this->Name = name;
}

CPrimitiveQuad *IEntity::getBody()
{
    return body;
}
void IEntity::setPosition(float x, float y)
{
    if (body != nullptr)
    {
        body->setPosition(x, y);
        Position.x = x;
        Position.y = y;
    }
}
void IEntity::setPosition(const sf::Vector2f &position)
{
    if (body != nullptr)
    {
        body->setPosition(position);
        this->Position = position;
    }
}
sf::Vector2f IEntity::getPosition() const
{
    return Position;
}
int IEntity::getNexId()
{
    return IEntity::currentId++;
}

IComponent *IEntity::getComponent(int id)
{
    for (auto c : Components)
    {
        if (c->getId() == id)
        {
            return c;
        }
    }
    return nullptr;
}
std::vector<CPrimitiveQuad *> IEntity::getDrawable()
{
    std::vector<CPrimitiveQuad *> result;
    for (auto &c : Components)
    {
        CPrimitiveQuad *p1 = dynamic_cast<CPrimitiveQuad *>(c);
        if (p1 != nullptr)
        {
            result.push_back(p1);
            std::cout << "Add component to " << getName() << std::endl;
        }
    }
    return result;
}

