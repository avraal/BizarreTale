// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by andrew on 02.04.18.
//
#include "CTile.h"

void CTile::LoadTexture(std::string ImagePath)
{
    if (!ImagePath.empty())
    {
        texture.loadFromFile(ImagePath);
    }
    sprite.setTexture(texture);
}

CTile::CTile(IEntity *entity, int id, const std::string &Name, std::string ImagePath, sf::Vector2f position, int index)
        : CPrimitiveQuad(entity, id, Name)
{
    std::cout << "TECtor" << std::endl;
    this->ImagePath = ImagePath;
    this->Name = Name;
    LoadTexture(ImagePath);
    this->index = index;
    setPosition(position.x, position.y);
}

CTile::CTile(const CTile &entity) : CTile(entity.entity, entity.id, entity.Name, entity.ImagePath, entity.getPosition(),
                                          entity.index)
{
    std::cout << "Copy ctor" << std::endl;
}

CTile::CTile(const CTile &&entity) : CTile(entity)
{
    std::cout << "Move ctor" << std::endl;
}

void CTile::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    //    states.texture = &texture;
    target.draw(sprite, states);
    target.draw(shape, states);
}

CTile::~CTile()
{
    //    std::cout << "Dcor??" << std::endl;
}
void CTile::setPosition(float x, float y)
{
    Transformable::setPosition(x, y);
    sprite.setPosition(x, y);
    drawBounds();
    if (!ShowBounds)
    {
        hideBounds();
    }
}
void CTile::setPosition(const sf::Vector2f &Position)
{
    this->setPosition(Position.x, Position.y);
}
std::string CTile::GetImagePath() const
{
    return ImagePath;
}

CTile &CTile::operator=(CTile const &me)
{
    if (this != &me)
    {
        this->ImagePath = me.GetImagePath();
        this->Name = me.Name;
        setPosition(me.getPosition().x, me.getPosition().y);
        LoadTexture(ImagePath);
    }
    return *this;
}
void CTile::setSize(sf::Vector2f s)
{
    sprite.setScale(s.x / sprite.getLocalBounds().width, s.y / sprite.getLocalBounds().height);
    std::cout << sprite.getGlobalBounds().width << " " << sprite.getGlobalBounds().height << std::endl;
    ShowBounds ? drawBounds() : hideBounds();
}

sf::Vector2f CTile::getSpriteScale() const
{
    return sprite.getScale();
}
std::string CTile::GetName() const
{
    return Name;
}
void CTile::drawBounds()
{
    shape.Hide();

    shape.append({getPosition(), getPosition() + sf::Vector2f(sprite.getGlobalBounds().width, 0)});
    shape.append({getPosition() + sf::Vector2f(sprite.getGlobalBounds().width, 0),
                  getPosition() + sf::Vector2f(sprite.getGlobalBounds().width, sprite.getGlobalBounds().height)});
    shape.append({getPosition() + sf::Vector2f(sprite.getGlobalBounds().width, sprite.getGlobalBounds().height),
                  sf::Vector2f(getPosition().x, getPosition().y + sprite.getGlobalBounds().height)});
    shape.append({getPosition(), sf::Vector2f(getPosition().x, getPosition().y + sprite.getGlobalBounds().height)});
}