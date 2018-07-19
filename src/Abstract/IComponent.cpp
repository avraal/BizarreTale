
// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by Andrew Volski on 10.07.18.
//

#include "IComponent.hpp"
IComponent::~IComponent()
{
}
void IComponent::setName(const std::string &name)
{
    this->Name = name;
}
std::string IComponent::getName() const
{
    return Name;
}
