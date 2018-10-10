
// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by Andrew Volski on 10.07.18.
//

#include "IComponent.hpp"
#include "../Entity/IEntity.hpp"

const std::string & IComponent::getName() const noexcept
{
    return name;
}

us_int IComponent::getId() const noexcept
{
    return id;
}
IComponent::IComponent(us_int id, us_int entityId, const std::string &name)
{
    this->id = id;
    this->entityId = entityId;
    this->name = name;
}
us_int IComponent::getEntityId() const noexcept
{
    return entityId;
}

IComponent::~IComponent()
{
}