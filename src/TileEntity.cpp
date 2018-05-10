// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by andrew on 02.04.18.
//
#include "TileEntity.h"

TileEntity::TileEntity()
{
    std::cout << "Default ctor" << std::endl;
    _imagePath = new char[1024];
    name = new char[512];
    strcpy(_imagePath, "");
    strcpy(name, "null");
    LoadTexture(_imagePath);
    sprite.setPosition(0, 0);
}

void TileEntity::LoadTexture(std::string imagePath)
{
    if(!texture.loadFromFile(imagePath))
    {
//        std::cerr << "[WARNING | TileEntity]: Failure load texture file" << std::endl;
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

TileEntity::TileEntity(const char *imagePath, sf::Vector2f position)
{
    std::cout << "Ctor" << std::endl;
    name = new char[512];
    _imagePath = new char[1024];
    strcpy(_imagePath, imagePath);
    strcpy(name, "Obj");
    LoadTexture(_imagePath);
    sprite.setPosition(position.x, position.y);
}

TileEntity::TileEntity(const TileEntity &entity)
{
    std::cout << "Copy ctor??" << std::endl;
    name = new char[512];
    _imagePath = new char[1024];
    strcpy(_imagePath, entity.getImagePath());
    strcpy(name, entity.name);
    LoadTexture(_imagePath);
    sprite.setPosition(entity.getPosition());
}

TileEntity::TileEntity(const TileEntity &&entity)
{
    std::cout << "Move ctor??" << std::endl;
    name = new char[512];
    _imagePath = new char[1024];
    strcpy(this->name, entity.name);
    strcpy(this->_imagePath, entity.getImagePath());
    LoadTexture(_imagePath);
    sprite.setPosition(entity.getPosition());
}

void TileEntity::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(sprite, states);
}

TileEntity::~TileEntity()
{
//    std::cout << "Dcor??" << std::endl;
}
void TileEntity::setPosition(float x, float y)
{
    sprite.setPosition(x, y);
}
const sf::Vector2f &TileEntity::getPosition() const
{
    return sprite.getPosition();
}
const sf::Vector2f &TileEntity::getScale() const
{
    return sprite.getScale();
}
sf::Vector2u TileEntity::getSize() const
{
    return texture.getSize();
}
void TileEntity::setPosition(sf::Vector2f Position)
{
    sprite.setPosition(Position);
}
char *TileEntity::getImagePath() const
{
    return _imagePath;
}
void TileEntity::LoadTexture(const char *imagePath)
{
    LoadTexture(std::string{imagePath});
}
TileEntity &TileEntity::operator=(TileEntity const &me)
{
    if(this != &me)
    {
        strcpy(_imagePath, me.getImagePath());
        strcpy(name, me.name);
        setPosition(me.getPosition());
        LoadTexture(_imagePath);
    }
    return *this;
}
