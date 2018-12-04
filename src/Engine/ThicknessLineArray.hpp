// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by Andrew Volski on 26.06.18.
//

#ifndef DEMIURGE_THICKNESSLINEARRAY_HPP
#define DEMIURGE_THICKNESSLINEARRAY_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <vector>
#include "ThicknessLine.hpp"

class ThicknessLineArray : public sf::Drawable
{
private:
    std::vector<ThicknessLine> lines;

public:
    ThicknessLineArray(){}
    void append(const ThicknessLine &line);
    void resize(us_int lineCount);
    void clear();
    void ChangeColor(sf::Color c);
    us_int getLineCount();

    ThicknessLine &operator[](us_int index);
    const ThicknessLine &operator[](us_int index) const;

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    virtual ~ThicknessLineArray() {}
};

#endif //DEMIURGE_THICKNESSLINEARRAY_HPP
