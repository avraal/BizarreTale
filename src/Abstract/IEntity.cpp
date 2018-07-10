
// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by Andrew Volski on 10.07.18.
//

#include "IEntity.hpp"
int IEntity::GetId()
{
    return Id;
}
void IEntity::setId(int id)
{
    //TODO: add checking on unique value
    this->Id = id;
}
void IEntity::addComponent(std::shared_ptr<IComponent> component)
{
    //TODO: add checking on unique value
    Components.push_back(component);
}
