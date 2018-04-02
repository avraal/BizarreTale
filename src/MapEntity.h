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

class MapEntity : public sf::Drawable
{
private:
    sf::Texture texture;
    sf::Sprite  sprite;

protected:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

public:
    MapEntity(const std::string imagePath, float posX = 0.f, float posY = 0.f);
    virtual ~MapEntity();

};

#endif //BIZARRETALE_MAPENTITY_H
