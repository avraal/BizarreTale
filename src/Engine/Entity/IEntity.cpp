
// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by Andrew Volski on 10.07.18.
//
#include <algorithm>
#include "IEntity.hpp"
#include "../Level.hpp"

us_int IEntity::currentId = 0;

IEntity::IEntity()
{
    id = IEntity::getNextId();
    Position = {.0f, .0f};
    name = "def";
}

us_int IEntity::getId() const noexcept
{
    return id;
}

void IEntity::addComponent(std::shared_ptr<IComponent> component)
{
    Components.push_back(component);
}
IEntity::~IEntity()
{
    std::cout << "dtor" << std::endl;
    Components.clear();
}

const std::string & IEntity::getName() const noexcept
{
    return name;
}
void IEntity::setName(const std::string &name) noexcept
{
    this->name = name;
}

sf::Vector2f IEntity::getPosition() const
{
    return Position;
}
us_int IEntity::getNextId()
{
    return IEntity::currentId++;
}

std::shared_ptr<IComponent> IEntity::getComponent(us_int id)
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

std::shared_ptr<IComponent> IEntity::getComponent(const std::string &Name)
{
    for (auto c : Components)
    {
        if (c->getName() == Name)
        {
            return c;
        }
    }
    return nullptr;
}
std::vector<std::shared_ptr<CPrimitiveQuad>> IEntity::getDrawable()
{
    std::vector<std::shared_ptr<CPrimitiveQuad>> result;
    for (auto c : Components)
    {
        std::shared_ptr<CPrimitiveQuad> p = std::dynamic_pointer_cast<CPrimitiveQuad>(c);
        if (p)
        {
            result.push_back(p);
        }
    }
    return result;
}
IEntity::IEntity(const IEntity &rhs)
{
    this->id = IEntity::getNextId();
    this->Components.clear();
    std::copy(rhs.Components.begin(), rhs.Components.end(), std::back_inserter(Components));
    this->name = rhs.name;
    this->Position = rhs.Position;
}
IEntity &IEntity::operator=(const IEntity &rhs)
{
    if(this != &rhs)
    {
        this->id = IEntity::getNextId();
        this->Components.clear();
        std::copy(rhs.Components.begin(), rhs.Components.end(), std::back_inserter(Components));
        this->name = rhs.name;
        this->Position = rhs.Position;
    }
    return *this;
}
void IEntity::removeComponent(us_int compId)
{
    auto target = std::remove_if(Components.begin(), Components.end(), [compId](std::weak_ptr<IComponent> comp)
    {
        if (comp.lock()->getId() == compId)
        {
            comp.lock()->release();
            return true;
        }
        return false;
    });

    Components.erase(target, Components.end());
}
void IEntity::removeComponents()
{
    for (const auto &component : Components)
    {
        component->release();
    }
    Components.clear();
}