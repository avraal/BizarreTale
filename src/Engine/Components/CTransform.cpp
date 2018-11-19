// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by Andrew Volski on 08.10.18.
//

#include "CTransform.hpp"
CTransform::CTransform(us_int id, us_int entityId, const std::string &name, const sf::Vector2f &pos) : IComponent(id, entityId, name)
{
    this->setPosition(pos);
}