// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by andrew on 02.04.18.
//
#include "TileEntity.h"

TileEntity::TileEntity() : PrimitiveQuad()
{
    std::cout << "Default ctor" << std::endl;
    ImagePath = "";
    Name = "Empty";
    LoadTexture(ImagePath);
    sprite.setPosition(getPosition());
}

void TileEntity::LoadTexture(std::string ImagePath)
{
    if (!ImagePath.empty())
    {
        texture.loadFromFile(ImagePath);
    }
    sprite.setTexture(texture);
}

TileEntity::TileEntity(std::string Name, std::string ImagePath, sf::Vector2f position, int index) : PrimitiveQuad()
{
    std::cout << "Ctor" << std::endl;
    this->ImagePath = ImagePath;
    this->Name = Name;
    LoadTexture(ImagePath);
    setIndex(index);
    setPosition(position.x, position.y);
}

TileEntity::TileEntity(const TileEntity &entity) : TileEntity(entity.Name, entity.GetImagePath(), entity.getPosition(),
                                                              entity.getIndex())
{
    std::cout << "Copy ctor" << std::endl;
}

TileEntity::TileEntity(const TileEntity &&entity) : TileEntity(entity)
{
    std::cout << "Move ctor" << std::endl;
}

void TileEntity::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
//    states.texture = &texture;
    target.draw(sprite, states);
}

TileEntity::~TileEntity()
{
    //    std::cout << "Dcor??" << std::endl;
}
void TileEntity::setPosition(float x, float y)
{
    Transformable::setPosition(x, y);
    sprite.setPosition(x, y);
}
std::string TileEntity::GetImagePath() const
{
    return ImagePath;
}

TileEntity &TileEntity::operator=(TileEntity const &me)
{
    if (this != &me)
    {
        this->ImagePath = me.GetImagePath();
        this->Name = me.Name;
        Transformable::setPosition(me.getPosition());
        LoadTexture(ImagePath);
    }
    return *this;
}
void TileEntity::setIndex(int index)
{
    this->index = index;
}
int TileEntity::getIndex() const
{
    return index;
}
void TileEntity::setSize(sf::Vector2f s)
{
    sprite.setScale(s.x / sprite.getLocalBounds().width, s.y / sprite.getLocalBounds().height);
}
sf::Vector2f TileEntity::getSpriteScale() const
{
    return sprite.getScale();
}
void TileEntity::setName(const std::string &Name)
{
    this->Name = Name;
}
std::string TileEntity::GetName() const
{
    return Name;
}