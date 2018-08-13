
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

IComponent::IComponent(std::shared_ptr<IEntity> entity, int id, const std::string &name)
{
    std::cout << "ICCtor" << std::endl;
    this->entity = entity;
    this->Name = name;
    this->id = id;
    std::cout << "IC name = " << shared_from_this()->Name << std::endl;
    try
    {
        if (this->entity)
        {
            this->entity->addComponent(shared_from_this());
        } else
        {
            std::cout << "IC bad add component" << std::endl;
        }
    }catch (std::bad_weak_ptr &ex)
    {
        std::cout << ex.what() << std::endl;
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
std::weak_ptr<IEntity> IComponent::getEntity()
{
    return entity;
}
