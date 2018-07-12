
// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by Andrew Volski on 12.07.18.
//

#include "EObject.hpp"
#include "../PrimitiveQuad.hpp"
EObject::EObject()
{
    setId(0);
    std::shared_ptr<IComponent> tile = std::make_shared<PrimitiveQuad>(sf::Color::Red);
    addComponent(tile);
}
EObject::~EObject()
{

}
