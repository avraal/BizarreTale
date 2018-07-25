// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by Andrew Volski on 26.06.18.
//

#include "ThicknessLineArray.hpp"
void ThicknessLineArray::append(const ThicknessLine &line)
{
    lines.push_back(line);
}
void ThicknessLineArray::resize(size_t lineCount)
{
    lines.resize(lineCount);
}
size_t ThicknessLineArray::getLineCount()
{
    return lines.size();
}
ThicknessLine &ThicknessLineArray::operator[](size_t index)
{
    return lines[index];
}

const ThicknessLine &ThicknessLineArray::operator[](size_t index) const
{
    return lines[index];
}
void ThicknessLineArray::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    for(auto l : lines)
    {
        target.draw(l, states);
    }
}
void ThicknessLineArray::Hide()
{
    lines.clear();
}
void ThicknessLineArray::ChangeColor(sf::Color c)
{
    for(auto &l : lines)
    {
        l.ChangeColor(c);
    }
}
