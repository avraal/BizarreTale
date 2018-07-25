// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by Andrew Volski on 10.05.18.
//

#include <SFML/Graphics/VertexArray.hpp>
#include <iostream>
#include "CPrimitiveQuad.hpp"
#include "CONST_DEFINITIONS.h"

CPrimitiveQuad::CPrimitiveQuad(sf::Color c)
{
    std::cout << "PQCtor" << std::endl;
    index = 0;
    this->color = c;
    body.setPrimitiveType(sf::PrimitiveType::Quads);
    body.resize(4);
    ShowBounds = false;
    setSize({TSD, TSD});
    shape = ThicknessLineArray();
}
CPrimitiveQuad::CPrimitiveQuad(const CPrimitiveQuad &p)
{
    std::cout << "Copy" << std::endl;
    this->color = p.color;
    this->index = p.index;
    this->body = p.body;
    this->ShowBounds = p.ShowBounds;
    setSize({TSD, TSD}); //TODO: Change TSD to real size
    shape = p.shape;
}
CPrimitiveQuad::CPrimitiveQuad(const CPrimitiveQuad &&p)
{
    std::cout << "Move" << std::endl;
    this->color = p.color;
    this->index = p.index;
    this->body = p.body;
    this->ShowBounds = p.ShowBounds;
    setSize({TSD, TSD}); //TODO: Change TSD to real size
    shape = p.shape;
}
void CPrimitiveQuad::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    states.texture = &texture;
    target.draw(body, states);
    target.draw(shape, states);
}
sf::Vector2u CPrimitiveQuad::getTextureSize() const
{
    return texture.getSize();
}
void CPrimitiveQuad::setSize(sf::Vector2f s)
{
    body[0].position = sf::Vector2f(0, 0);
    body[1].position = sf::Vector2f(s.x, 0);
    body[2].position = sf::Vector2f(s.x, s.y);
    body[3].position = sf::Vector2f(0, s.x);

    body[0].texCoords = sf::Vector2f(0, 0);
    body[1].texCoords = sf::Vector2f(s.x, 0);
    body[2].texCoords = sf::Vector2f(s.x, s.y);
    body[3].texCoords = sf::Vector2f(0, s.x);

    image.create(s.x, s.y, color);
    texture.loadFromImage(image);
}
CPrimitiveQuad::~CPrimitiveQuad()
{
}
void CPrimitiveQuad::changeVertexColor(sf::Color c)
{
    shape.ChangeColor(c);
}
void CPrimitiveQuad::drawBounds()
{
    shape.Hide();
    shape.append({body[0].position, body[1].position});
    shape.append({body[1].position, body[2].position});
    shape.append({body[2].position, body[3].position});
    shape.append({body[3].position, body[0].position});
}
void CPrimitiveQuad::hideBounds()
{
    shape.Hide();
    ShowBounds = false;
}
sf::Color CPrimitiveQuad::getColor() const
{
    return color;
}
int CPrimitiveQuad::getIndex() const
{
    return index;
}
void CPrimitiveQuad::setIndex(int index)
{
    this->index = index;
}
void CPrimitiveQuad::setPosition(float x, float y)
{
    Transformable::setPosition(x, y);
}
void CPrimitiveQuad::setPosition(const sf::Vector2f &Position)
{
    Transformable::setPosition(Position);
}

