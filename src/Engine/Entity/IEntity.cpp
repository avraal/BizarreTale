
// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by Andrew Volski on 10.07.18.
//
#include <algorithm>
#include "IEntity.hpp"
#include "../Level.hpp"

us_int IEntity::getId() const noexcept
{
    return id;
}

const std::string & IEntity::getName() const noexcept
{
    return name;
}
void IEntity::setName(const std::string &name) noexcept
{
    this->name = name;
}
IEntity::IEntity(us_int id, const std::string &name)
{
    this->id = id;
    this->name = name;
}
IEntity::~IEntity()
{
}