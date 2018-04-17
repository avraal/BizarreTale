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
#include <cstring>
#include "CONST_DEFINITIONS.h"

class MapEntity : public sf::Drawable
{
private:
    sf::Texture texture;
    sf::Sprite sprite;

    void LoadTexture(std::string imagePath);
    void LoadTexture(const char* imagePath);

protected:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

public:
    MapEntity(const char *imagePath, sf::Vector2f position = {.0f, .0f});
    MapEntity(const MapEntity &entity);
    MapEntity(const MapEntity &&entity);
    MapEntity();
    virtual ~MapEntity();
    virtual void setPosition(float x, float y);
    virtual void setPosition(sf::Vector2f Position);
    virtual const sf::Vector2f &getPosition() const;
    virtual const sf::Vector2f &getScale() const;
    virtual sf::Vector2u getSize() const;
    char *getImagePath() const;
    char *name;
    char *_imagePath;

};

#endif //BIZARRETALE_MAPENTITY_H
