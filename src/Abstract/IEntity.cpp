
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
    Id = IEntity::getNextId();
    Position = {.0f, .0f};
    Name = "def";
}

int IEntity::GetId() const noexcept
{
    return Id;
}

void IEntity::addComponent(std::shared_ptr<IComponent> component)
{
    Components.push_back(component);
}
IEntity::~IEntity()
{
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

sf::Vector2f IEntity::getPosition() const
{
    return Position;
}
int IEntity::getNextId()
{
    return IEntity::currentId++;
}

std::weak_ptr<IComponent> IEntity::getComponent(int id)
{
    for (auto c : Components)
    {
        if (c.lock()->getId() == id)
        {
            return c;
        }
    }
//    return nullptr;
}

std::weak_ptr<IComponent> IEntity::getComponent(const std::string &Name)
{
    for (auto c : Components)
    {
        if (c.lock()->getName() == Name)
        {
            return c;
        }
    }
}
std::vector<std::shared_ptr<CPrimitiveQuad>> IEntity::getDrawable()
{
    std::vector<std::shared_ptr<CPrimitiveQuad>> result;
    for (auto c : Components)
    {
        std::shared_ptr<CPrimitiveQuad> p = std::dynamic_pointer_cast<CPrimitiveQuad>(c.lock());
        if (p)
        {
            result.push_back(p);
            std::cout << "Add component " << p->getName() << ':' << p->getId() << " to " << getName() << std::endl;
        }
    }
    std::cout << result.size() << std::endl;
    return result;
}
IEntity::IEntity(const IEntity &rhs)
{
    this->Id = IEntity::getNextId();
    this->Components.clear();
    std::copy(rhs.Components.begin(), rhs.Components.end(), std::back_inserter(Components));
    this->Name = rhs.Name;
    this->Position = rhs.Position;
}
IEntity &IEntity::operator=(const IEntity &rhs)
{
    if(this != &rhs)
    {
        this->Id = IEntity::getNextId();
        this->Components.clear();
        std::copy(rhs.Components.begin(), rhs.Components.end(), std::back_inserter(Components));
        this->Name = rhs.Name;
        this->Position = rhs.Position;
    }
    return *this;
}
