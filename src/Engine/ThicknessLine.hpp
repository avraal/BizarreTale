// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by Andrew Volski on 26.06.18.
//

#ifndef BIZARRETALE_THICKNESSLINE_HPP
#define BIZARRETALE_THICKNESSLINE_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <iostream>
#include <cmath>
#include "CONST_DEFINITIONS.h"

class ThicknessLine : public sf::Drawable
{
public:
    ThicknessLine(const sf::Vector2f &point1, const sf::Vector2f &point2) : color(sf::Color::Red), thickness(3.f)
    {
        sf::Vector2f direction = point2 - point1;
        sf::Vector2f unitDirection = direction / std::sqrt(direction.x * direction.x + direction.y * direction.y);
        sf::Vector2f unitPerpendicular(-unitDirection.y, unitDirection.x);

        sf::Vector2f offset = (thickness / 2.f) * unitPerpendicular;

        vertices[0].position = point1 + offset;
        vertices[1].position = point2 + offset;
        vertices[2].position = point2 - offset;
        vertices[3].position = point1 - offset;

        Show();
    }
    ThicknessLine(ThicknessLine *l)
    {
        vertices[0] = l->vertices[0];
        vertices[1] = l->vertices[1];
        vertices[2] = l->vertices[2];
        vertices[3] = l->vertices[3];
        color = l->color;
        thickness = l->thickness;
    }
    void ChangeColor(sf::Color c)
    {
        for(us_int i = 0; i < 4; i++)
        {
            vertices[i].color = c;
        }
    }

    void Show()
    {
        for(us_int i = 0; i < 4; i++)
        {
            vertices[i].color = color;
        }
    }
    ThicknessLine() : color(sf::Color::Red), thickness(3.f) {}
private:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override
    {
        target.draw(vertices, 4, sf::Quads, states);
    }
    sf::Color color;
    sf::Vertex vertices[4];
    float thickness;
};

#endif //BIZARRETALE_THICKNESSLINE_HPP
