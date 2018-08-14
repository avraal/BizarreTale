
// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by Andrew Volski on 10.07.18.
//

#include "IComponent.hpp"
#include "IEntity.hpp"
#include "../Util/IDGenerator.hpp"
IComponent::IComponent()
{
    this->id = IDGenerator::getId();
}

IComponent::IComponent(int id, const std::string &name)
{
    std::cout << "ICCtor" << std::endl;
    this->Name = name;
    this->id = id;
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
std::shared_ptr<IEntity> IComponent::getEntity()
{
    return entity;
}
void IComponent::Attach(std::shared_ptr<IEntity> entity)
{
    this->entity = entity;
    entity->addComponent(shared_from_this());
}