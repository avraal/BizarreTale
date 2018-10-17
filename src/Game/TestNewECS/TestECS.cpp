// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by Andrew Volski on 09.10.18.
//

#include "TestECS.hpp"
#include "../../Engine/Entity/EObject.hpp"
#include "../../Engine/Systems/Managers/EntityManager.hpp"
#include "../../Engine/Systems/Managers/ComponentManager.hpp"
TestECS::TestECS(const std::string &name) : Level(name)
{

}
bool TestECS::prepareLevel(sf::RenderWindow &window)
{
    Level::prepareLevel(window);

    tileSizeX = 10;
    tileSizeY = 10;

    TilesIds = new us_int *[tileSizeX];
    for (us_int i = 0; i < tileSizeX; i++)
    {
        TilesIds[i] = new us_int[tileSizeY];
    }

    for (us_int i = 0; i < tileSizeX; i++)
    {
        for (us_int j = 0; j < tileSizeY; j++)
        {
            EObject *tile = static_cast<EObject *>(EntityManager::Create(GetClassName::Get<EObject>(),
                                                                         "tile" + std::to_string(i)));
            tile->transform =
                    static_cast<CTransform *>(ComponentManager::Create(GetClassName::Get<CTransform>(), tile->getId(),
                                                                       "transform"));
            tile->body =
                    static_cast<CDrawable *>(ComponentManager::Create(GetClassName::Get<CDrawable>(), tile->getId(),
                                                                      "body"));
            tile->setPosition(sf::Vector2i(i * TILE_SIZE_DEFAULT, j * TILE_SIZE_DEFAULT));
            addObject(tile->getId());
            TilesIds[i][j] = tile->getId();
        }
    }
    //vertical lines
    for (us_int i = 0; i < tileSizeX; i++)
    {
        EObject *tileStart = static_cast<EObject *>(EntityManager::getEntity(TilesIds[i][0]));
        EObject *tileEnd = static_cast<EObject *>(EntityManager::getEntity(TilesIds[tileSizeX-1][tileSizeY-1]));
        sf::Vertex line [] =
                {
                    sf::Vertex({tileStart->transform->getPosition().x, tileStart->transform->getPosition().y}, sf::Color(42, 76, 61)),
                    sf::Vertex({tileStart->transform->getPosition().x, tileEnd->transform->getPosition().y + TILE_SIZE_DEFAULT}, sf::Color(42, 76, 61))
                };
        LineGrid.emplace_back(std::pair<sf::Vertex, sf::Vertex>(line[0], line[1]));
    }

    UserInterface->gui->add(infoPanel);
    return true;
}
void TestECS::draw(sf::RenderWindow &window)
{
    Level::draw(window);
    for (auto g : LineGrid)
    {
        sf::Vertex line[] =
                {
                        g.first,
                        g.second
                };
        window.draw(line, 2, sf::Lines);
    }
    infoFPSLabel->setText("FPS: " + std::to_string((us_int) fps));
}
void TestECS::MouseCallbacks(sf::RenderWindow &window, sf::Event &event)
{

}
void TestECS::KeyBoardCallbacks(sf::RenderWindow &window, sf::Event &event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        switch (event.key.code)
        {
            case sf::Keyboard::Escape:
            {
                window.close();
                break;
            }
        }
    }
}
void TestECS::HandleGUIEvent(sf::Event &event)
{
    Level::HandleGUIEvent(event);
}
void TestECS::loadGui(sf::RenderWindow &window)
{
    infoFPSLabel = tgui::Label::create();
    infoFPSLabel->getRenderer()->setTextColor(sf::Color::White);
    infoFPSLabel->setTextSize(INFO_PANEL_TEXT_SIZE);

    infoPanel = tgui::Panel::create({200, 100});
    infoPanel->setPosition(window.getSize().x - infoPanel->getSize().x, 0);
    infoPanel->getRenderer()->setBackgroundColor(sf::Color(0, 0, 0, 128));
    infoPanel->add(infoFPSLabel);
}
