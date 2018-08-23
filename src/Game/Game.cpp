
// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by Andrew Volski on 20.08.18.
//

#include <dirent.h>
#include <cstring>
#include <iostream>
#include "Game.hpp"
#include "../Engine/CONST_DEFINITIONS.h"
#include "../Engine/MapEditor.h"
Game::Game(const std::string &title)
{
    this->Title = title;
    levelManager = std::make_unique<LevelManager>();
    auto editor = std::make_shared<MapEditor>("MapEditor");
    levelManager->registerLevel(editor);
}

bool Game::start()
{
    window.create(sf::VideoMode(WINDOW_SIZE_HD_WIDTH, WINDOW_SIZE_HD_HEIGHT), Title);
    MainCamera = window.getView();
    MainCamera.setCenter(WINDOW_SIZE_HD_WIDTH * 0.35, WINDOW_SIZE_HD_HEIGHT * 0.45);

    CurrentLevel = levelManager->loadLevel("MapEditor");
    if (!CurrentLevel)
    {
        return false;
    }
    std::cout << "Load " << CurrentLevel->getName() << std::endl;
    CurrentLevel->ImageDirectory = this->ImageDirectory;
    if (!CurrentLevel->prepareLevel(window))
    {
        return false;
    }
    CurrentLevel->setCamera(MainCamera);
    window.setKeyRepeatEnabled(true);
    window.setVerticalSyncEnabled(true);

    while (window.isOpen())
    {
        sf::Event event;
        window.clear(sf::Color(42, 76, 61));

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            CurrentLevel->MouseCallbacks(window, event);
            CurrentLevel->KeyBoardCallbacks(window, event);
            CurrentLevel->HandleGUIEvent(event);
        }
        window.setView(MainCamera);

        CurrentLevel->draw(window);
        window.display();
    }
    return true;
}