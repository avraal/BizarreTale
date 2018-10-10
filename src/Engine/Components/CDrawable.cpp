// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by Andrew Volski on 08.10.18.
//

#include "CDrawable.hpp"
CDrawable::CDrawable(us_int id, us_int entityId, const std::string &name, const std::string &ImagePath, sf::Color c,
                     us_int index) : IComponent(id, entityId, name)
{
    this->color = c;
    this->index = index;
    this->ImagePath = ImagePath;
}
const sf::Color &CDrawable::getColor() const
{
    return color;
}
us_int CDrawable::getIndex() const
{
    return index;
}
const std::string &CDrawable::getImagePath() const
{
    return ImagePath;
}
void CDrawable::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(body, states);
    target.draw(bounds, states);
}
const sf::Texture &CDrawable::getTexture() const
{
    return texture;
}
