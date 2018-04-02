//
// Created by andrew on 02.04.18.
//
#include "MapEntity.h"

MapEntity::MapEntity(const std::string imagePath, float posX, float posY)
{
    if (!texture.loadFromFile(imagePath))
    {
        std::cerr << "[ERROR | MapEntity]: Failure load texture file" << std::endl;
    } else
    {
        sprite.setTexture(texture);
    }
    sprite.setScale(0.1f, 0.1f);

    sprite.setPosition(posX, posY);

}
void MapEntity::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(sprite, states);
}

MapEntity::~MapEntity()
{
}
