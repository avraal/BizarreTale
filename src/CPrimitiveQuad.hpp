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
#include "ThicknessLine.hpp"
#include "ThicknessLineArray.hpp"
#include "Abstract/IComponent.hpp"
#include "CONST_DEFINITIONS.h"

#define TSD TILE_SIZE_DEFAULT

class CPrimitiveQuad : public sf::Drawable, public sf::Transformable, public IComponent
{
private:
    sf::Color color;

public:
    CPrimitiveQuad(sf::Color c = sf::Color(91, 97, 91));
    CPrimitiveQuad(int id, const std::string &name, sf::Color c = sf::Color(91, 97, 91));
    CPrimitiveQuad(const CPrimitiveQuad &);
    CPrimitiveQuad(const CPrimitiveQuad &&);
    sf::Vector2u getTextureSize() const;
    sf::Color getColor() const;
    virtual ~CPrimitiveQuad();
    virtual void setSize(sf::Vector2f s);
    virtual void changeVertexColor(sf::Color c);
    virtual void drawBounds();
    virtual void hideBounds();
    virtual void Attach(std::shared_ptr<IEntity> ptr) override;
    virtual void setPosition(float x, float y);
    virtual void setPosition(const sf::Vector2f &Position);
    virtual std::string &getTexturePath();
    const sf::Texture *getTexture() const;
    int getIndex() const;
    void setIndex(int index);
    bool ShowBounds;
protected:
    std::string ImagePath = "";
    int index;
    sf::VertexArray body;
    sf::Texture texture;
    sf::Image image;
    ThicknessLineArray shape;
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};

#endif //BIZARRETALE_TESTQUAD_HPP
