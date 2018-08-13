
// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by Andrew Volski on 10.07.18.
//

#include "IComponent.hpp"
#include "IEntity.hpp"

IComponent::IComponent(IEntity *entity, int id, const std::string &name)
{
    this->entity = entity;
    this->Name = name;
    this->id = id;
    if (entity != nullptr)
    {
        entity->addComponent(this);
    }
}
std::string IComponent::getName() const noexcept
{
    return Name;
}
IComponent::~IComponent()
{
}
int IComponent::getId() const noexcept
{
    return id;
}
IEntity *IComponent::getEntity()
{
    return entity;
}
