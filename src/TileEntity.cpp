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
    if(!ImagePath.empty())
    {
        texture.loadFromFile(ImagePath);
    }
    sprite.setTexture(texture);
}

TileEntity::TileEntity(std::string ImagePath, sf::Vector2f position)
{
    std::cout << "Ctor" << std::endl;
    this->ImagePath = ImagePath;
    this->Name = "Empty";
    LoadTexture(ImagePath);
    SetPosition(position.x, position.y);
}

TileEntity::TileEntity(const TileEntity &entity) : TileEntity(entity.GetImagePath(), entity.getPosition())
{
}

TileEntity::TileEntity(const TileEntity &&entity) : TileEntity(entity)
{
}

void TileEntity::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(sprite, states);
}

//TileEntity::~TileEntity()
//{
////    std::cout << "Dcor??" << std::endl;
//}
void TileEntity::SetPosition(float x, float y)
{
    setPosition(x, y);
    sprite.setPosition(x, y);
}
std::string TileEntity::GetImagePath() const
{
    return ImagePath;
}

TileEntity &TileEntity::operator=(TileEntity const &me)
{
    if(this != &me)
    {
        this->ImagePath = me.GetImagePath();
        this->Name = me.Name;
        setPosition(me.getPosition());
        LoadTexture(ImagePath);
    }
    return *this;
}