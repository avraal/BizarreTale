// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by Andrew Volski on 09.10.18.
//

#ifndef DEMIURGE_TESTECS_HPP
#define DEMIURGE_TESTECS_HPP

#include "../../Engine/Level.hpp"

class TestECS : public Level
{
private:
    us_int **TilesIds;
    us_int tileSizeX;
    us_int tileSizeY;

    tgui::Label::Ptr infoFPSLabel;
    tgui::Panel::Ptr infoPanel;

    std::vector<std::pair<sf::Vertex, sf::Vertex>> LineGrid;
public:
    TestECS(const std::string &name);
    virtual ~TestECS() {}

    virtual bool prepareLevel(sf::RenderWindow &window) override;
    virtual void draw(sf::RenderWindow &window) override;
    virtual void MouseCallbacks(sf::RenderWindow &window, sf::Event &event) override;
    virtual void KeyBoardCallbacks(sf::RenderWindow &window, sf::Event &event) override;
    virtual void HandleGUIEvent(sf::Event &event) override;
protected:
    virtual void loadGui(sf::RenderWindow &window) override;
};

#endif //DEMIURGE_TESTECS_HPP
