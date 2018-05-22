
// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by Andrew Volski on 10.05.18.
//

#include <SFML/Graphics/VertexArray.hpp>
#include <iostream>
#include "PrimitiveQuad.hpp"
#include "CONST_DEFINITIONS.h"
PrimitiveQuad::PrimitiveQuad()
{
    hasChanged = true;
    body.setPrimitiveType(sf::PrimitiveType::Quads);
    body.resize(4);
    setSize({TSD, TSD});
}
void PrimitiveQuad::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    states.texture = &texture;
    target.draw(body, states);
    hasChanged = false;
}
sf::Vector2u PrimitiveQuad::getSize() const
{
    return texture.getSize();
}
bool PrimitiveQuad::getChanged()
{
    return hasChanged;
}
void PrimitiveQuad::setSize(sf::Vector2f s)
{
    body[0].position = sf::Vector2f(0, 0);
    body[1].position = sf::Vector2f(s.x, 0);
    body[2].position = sf::Vector2f(s.x, s.y);
    body[3].position = sf::Vector2f(0, s.x);

    body[0].texCoords = sf::Vector2f(0, 0);
    body[1].texCoords = sf::Vector2f(s.x, 0);
    body[2].texCoords = sf::Vector2f(s.x, s.y);
    body[3].texCoords = sf::Vector2f(0, s.x);

    image.create(s.x, s.y, sf::Color(91, 97, 91));
    texture.loadFromImage(image);
}
PrimitiveQuad::~PrimitiveQuad()
{

}
