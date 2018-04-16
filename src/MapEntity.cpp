//
// Created by andrew on 02.04.18.
//
#include "MapEntity.h"

MapEntity::MapEntity(const std::string imagePath, sf::Vector2f position)
{
    if (!texture.loadFromFile(imagePath))
    {
        std::cerr << "[WARNING | MapEntity]: Failure load texture file" << std::endl;
        sf::Image image;
        image.create(TILE_SIZE_DEFAULT, TILE_SIZE_DEFAULT, sf::Color(91, 97, 91));
        texture.loadFromImage(image);
        sprite.setTexture(texture);
    } else
    {
        sprite.setTexture(texture);
    }
    sprite.setPosition(position.x, position.y);
    name = "Obj";
}

void MapEntity::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(sprite, states);
}

MapEntity::~MapEntity()
{
    //    std::cout << "Dcor??" << std::endl;
}
void MapEntity::setPosition(float x, float y)
{
    sprite.setPosition(x, y);
}
const sf::Vector2f &MapEntity::getPosition() const
{
    return sprite.getPosition();
}
const sf::Vector2f &MapEntity::getScale() const
{
    return sprite.getScale();
}
MapEntity::MapEntity(const MapEntity &entity)
{
        std::cout << "Copy ctor??" << std::endl;
}
MapEntity::MapEntity(const MapEntity &&entity)
{
        std::cout << "Move ctor??" << std::endl;
}
sf::Vector2u MapEntity::getSize() const
{
    return texture.getSize();
}
void MapEntity::setPosition(sf::Vector2f Position)
{
    sprite.setPosition(Position);
}
