// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by Andrew Volski on 08.10.18.
//

#ifndef DEMIURGE_CDRAWABLE_HPP
#define DEMIURGE_CDRAWABLE_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "IComponent.hpp"
#include "../ThicknessLineArray.hpp"

class CDrawable : public IComponent, public sf::Drawable, public CRegisterable<CDrawable>
{
protected:
    CDrawable(us_int id, us_int entityId, const std::string &name, const std::string &ImagePath,
                  sf::Color c = sf::Color(91, 97, 91), us_int index = 0);

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    us_int index;
    std::string ImagePath;
    sf::VertexArray body;
    sf::Texture texture;
    ThicknessLineArray bounds;
private:
    friend class CRegisterable<CDrawable>;
    virtual ~CDrawable() {}
    sf::Color color;

public:
    const sf::Color &getColor() const;
    us_int getIndex() const;
    const std::string &getImagePath() const;
    const sf::Texture &getTexture() const;
    virtual void setPosition(sf::Vector2f p);
    virtual void initBounds();
};

#endif //DEMIURGE_CDRAWABLE_HPP
