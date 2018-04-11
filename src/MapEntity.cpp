//
// Created by andrew on 02.04.18.
//
#include "MapEntity.h"

MapEntity::MapEntity(const std::string imagePath, float posX, float posY)
{
    if (!texture.loadFromFile(imagePath))
    {
        std::cerr << "[WARNING | MapEntity]: Failure load texture file" << std::endl;
        sf::Image image;
        image.create(64, 64, sf::Color(91, 97, 91));
        texture.loadFromImage(image);
        sprite.setTexture(texture);
    } else
    {
        sprite.setTexture(texture);
    }
    sprite.setPosition(posX, posY);

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
//    std::cout << "Copy ctor??" << std::endl;
}
MapEntity::MapEntity(const MapEntity &&entity)
{
//    std::cout << "Move ctor??" << std::endl;
}
sf::Vector2u MapEntity::getSize() const
{
    return texture.getSize();
}
