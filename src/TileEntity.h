// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by andrew on 02.04.18.
//

#ifndef BIZARRETALE_MAPENTITY_H
#define BIZARRETALE_MAPENTITY_H

#include <iostream>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <cstring>
#include "CONST_DEFINITIONS.h"
#include "PrimitiveQuad.hpp"

class TileEntity : public PrimitiveQuad
{
private:
    sf::Sprite sprite;
    std::string ImagePath;
    int index = 0;

protected:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

public:
    TileEntity();
    TileEntity(std::string ImagePath, sf::Vector2f position = {.0f, .0f});
    TileEntity(const TileEntity &entity);
    TileEntity(const TileEntity &&entity);
    TileEntity &operator=(sf::Drawable const &) = delete;
    TileEntity &operator=(TileEntity const &me);


    virtual ~TileEntity();
    void LoadTexture(std::string ImagePath);
    void SetPosition(float x, float y);
    void setIndex(int index);
    std::string GetImagePath() const;
    int getIndex();

    std::string Name;
};

#endif //BIZARRETALE_MAPENTITY_H
