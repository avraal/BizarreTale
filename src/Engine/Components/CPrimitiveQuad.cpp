// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by Andrew Volski on 10.05.18.
//

#include <SFML/Graphics/VertexArray.hpp>
#include <iostream>
#include "CPrimitiveQuad.hpp"
#include "../Entity/IEntity.hpp"
#include "../CONST_DEFINITIONS.hpp"
CPrimitiveQuad::CPrimitiveQuad(sf::Color c)
{
    index = 0;
    this->color = c;
    body.setPrimitiveType(sf::PrimitiveType::Quads);
    body.resize(4);
    ShowBounds = false;
    setSize({TSD, TSD});
    shape = ThicknessLineArray();
}

CPrimitiveQuad::CPrimitiveQuad(us_int id, const std::string &name, sf::Color c) : IComponent(id, name)
{
    index = 0;
    this->color = c;
    body.setPrimitiveType(sf::PrimitiveType::Quads);
    body.resize(4);
    ShowBounds = false;
    setSize({TSD, TSD});
    shape = ThicknessLineArray();
}
CPrimitiveQuad::CPrimitiveQuad(const CPrimitiveQuad &p) : IComponent(p.id, p.name)
{
    std::cout << "СЗCopy" << std::endl;
    this->color = p.color;
    this->index = p.index;
    this->body = p.body;
    this->ShowBounds = p.ShowBounds;
    setSize({TSD, TSD}); //TODO: Change TSD to real size
    shape = p.shape;
}
CPrimitiveQuad::CPrimitiveQuad(const CPrimitiveQuad &&p) : IComponent(p.id, p.name)
{
    std::cout << "СЗMove" << std::endl;
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
    return {static_cast<unsigned int>(body.getBounds().width),
            static_cast<unsigned int>(body.getBounds().height)};
}
void CPrimitiveQuad::setSize(sf::Vector2f s)
{
    body[0].position = sf::Vector2f(0, 0);
    body[1].position = sf::Vector2f(s.x, 0);
    body[2].position = sf::Vector2f(s.x, s.y);
    body[3].position = sf::Vector2f(0, s.x);

    body[0].color = color;
    body[1].color = color;
    body[2].color = color;
    body[3].color = color;

    body[0].texCoords = sf::Vector2f(0, 0);
    body[1].texCoords = sf::Vector2f(s.x, 0);
    body[2].texCoords = sf::Vector2f(s.x, s.y);
    body[3].texCoords = sf::Vector2f(0, s.x);

//    image.create(s.x, s.y, color);
//    texture.loadFromImage(image);
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
us_int CPrimitiveQuad::getIndex() const
{
    return index;
}
void CPrimitiveQuad::setIndex(us_int index)
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
const sf::Texture *CPrimitiveQuad::getTexture() const
{
    return &texture;
}
std::string &CPrimitiveQuad::getTexturePath()
{
    return ImagePath;
}
void CPrimitiveQuad::Attach(std::shared_ptr<IEntity> ptr)
{
    IComponent::Attach(ptr);
    setPosition(ptr->getPosition());
}
void CPrimitiveQuad::release()
{
    body.clear();
    shape.clear();
}
std::ostream &operator<<(std::ostream &os, const CPrimitiveQuad &cp)
{
    cp.outputSerialize(os);
    return os;
}
void CPrimitiveQuad::outputSerialize(std::ostream &os) const
{
    IComponent::outputSerialize(os);
    os << "Index: " << index << '\n';
    os << "Color: R(" << color.r << ") G(" << color.g << ") B(" << color.b << ")\n";
    os << "Texture Size: " << getTextureSize().x << 'x' << getTextureSize().y << '\n';
    os << "Show Bounds: " << ShowBounds << '\n';
    os << "Position: X(" << getPosition().x << ") Y(" << getPosition().y << ")\n";
    os << "Image: " << ImagePath << "\n";
}
