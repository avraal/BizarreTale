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
#include "CPrimitiveQuad.hpp"

class CTile : public CPrimitiveQuad
{
private:
    sf::Sprite sprite;

protected:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

public:
    CTile() = delete;
    CTile(us_int id, const std::string &Name, std::string ImagePath, sf::Vector2f position, us_int index = 0);
    CTile(const CTile &tile);
    CTile(const CTile &&tile);
    CTile &operator=(sf::Drawable const &) = delete;

    CTile &operator=(CTile const &me);
    virtual ~CTile();
    void LoadTexture(std::string ImagePath);
    virtual void setPosition(float x, float y);
    virtual void setPosition(const sf::Vector2f &Position);
    virtual void setSize(sf::Vector2f s) override;
    virtual void drawBounds() override;
    std::string GetImagePath() const;
    std::string GetName() const;
    sf::Vector2f getSpriteScale() const;
};

#endif //BIZARRETALE_MAPENTITY_H
