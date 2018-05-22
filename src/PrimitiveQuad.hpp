
// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by Andrew Volski on 10.05.18.
//

#ifndef BIZARRETALE_TESTQUAD_HPP
#define BIZARRETALE_TESTQUAD_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>

#define TSD TILE_SIZE_DEFAULT

class PrimitiveQuad : public sf::Drawable, public sf::Transformable
{
public:
    PrimitiveQuad();
    virtual ~PrimitiveQuad();
    sf::Vector2u getSize() const;
    virtual void setSize(sf::Vector2f s);
    bool getChanged();
protected:
    sf::VertexArray body;
    sf::Texture texture;
    sf::Image image;
    mutable bool hasChanged;
protected:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};

#endif //BIZARRETALE_TESTQUAD_HPP
