// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by Andrew Volski on 26.06.18.
//

#ifndef BIZARRETALE_THICKNESSLINESTRIP_HPP
#define BIZARRETALE_THICKNESSLINESTRIP_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include "ThicknessLine.hpp"

class ThicknessLineArray : public sf::Drawable
{
private:
    std::vector<ThicknessLine> lines;

public:
    ThicknessLineArray(){}
    void append(const ThicknessLine &line);
    void resize(size_t lineCount);
    void Hide();
    void ChangeColor(sf::Color c);
    size_t getLineCount();

    ThicknessLine &operator[](size_t index);
    const ThicknessLine &operator[](size_t index) const;

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    virtual ~ThicknessLineArray() {}
};

#endif //BIZARRETALE_THICKNESSLINESTRIP_HPP
