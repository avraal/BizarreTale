//
// Created by andrew on 02.04.18.
//
#include "MapEntity.h"

MapEntity::MapEntity()
{
    _imagePath = new char[1024];
    name = new char[512];
    strcpy(_imagePath, "");
    strcpy(name, "null");
    LoadTexture(_imagePath);
    sprite.setPosition(0, 0);
}

void MapEntity::LoadTexture(std::string imagePath)
{
    if(!texture.loadFromFile(imagePath))
    {
//        std::cerr << "[WARNING | MapEntity]: Failure load texture file" << std::endl;
        sf::Image image;
        image.create(TILE_SIZE_DEFAULT, TILE_SIZE_DEFAULT, sf::Color(91, 97, 91));
        texture.loadFromImage(image);
        sprite.setTexture(texture);
    }
    else
    {
        sprite.setTexture(texture);
    }
}

MapEntity::MapEntity(const char *imagePath, sf::Vector2f position)
{
    _imagePath = new char[1024];
    name = new char[512];
    strcpy(_imagePath, imagePath);
    strcpy(name, "Obj");
    LoadTexture(_imagePath);
    sprite.setPosition(position.x, position.y);
}

MapEntity::MapEntity(const MapEntity &entity)
{
    std::cout << "Copy ctor??" << std::endl;
    _imagePath = new char[1024];
    name = new char[512];
    strcpy(_imagePath, entity.getImagePath());
    strcpy(name, entity.name);
    LoadTexture(_imagePath);
    sprite.setPosition(entity.getPosition());
}

MapEntity::MapEntity(const MapEntity &&entity)
{
    std::cout << "Move ctor??" << std::endl;
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
sf::Vector2u MapEntity::getSize() const
{
    return texture.getSize();
}
void MapEntity::setPosition(sf::Vector2f Position)
{
    sprite.setPosition(Position);
}
char *MapEntity::getImagePath() const
{
    return _imagePath;
}
void MapEntity::LoadTexture(const char *imagePath)
{
    LoadTexture(std::string{imagePath});
}