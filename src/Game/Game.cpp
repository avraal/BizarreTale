
// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by Andrew Volski on 20.08.18.
//

#include <dirent.h>
#include <cstring>
#include <iostream>
#include <thread>
#include "Game.hpp"
#include "../Engine/CONST_DEFINITIONS.hpp"
#include "../Engine/MapEditor.hpp"
#include "Labyrinth/Labyrinth.hpp"
Game::Game(const std::string &title)
{
    this->Title = title;
    levelManager = std::make_unique<LevelManager>();
//    auto editor = std::make_shared<MapEditor>("MapEditor");
    auto labyrinth = std::make_shared<Labyrinth>("Labyrinth");
//    auto testEcs = std::make_shared<TestECS>("TestECS");
//    levelManager->registerLevel(editor);
//    levelManager->registerLevel(testEcs);
    levelManager->registerLevel(labyrinth);
}

bool Game::start()
{
    window.create(sf::VideoMode(WINDOW_SIZE_HD_WIDTH, WINDOW_SIZE_HD_HEIGHT), Title);
    MainCamera = window.getView();
    MainCamera.setCenter(WINDOW_SIZE_HD_WIDTH * 0.25, WINDOW_SIZE_HD_HEIGHT * 0.45);

//    CurrentLevel = levelManager->loadLevel("MapEditor");
    CurrentLevel = levelManager->loadLevel("Labyrinth");
//    CurrentLevel = levelManager->loadLevel("TestECS");
    if (!CurrentLevel)
    {
        return false;
    }
    CurrentLevel->ImageDirectory = this->ImageDirectory;
    if (!CurrentLevel->prepareLevel(window))
    {
        return false;
    }
    CurrentLevel->setCamera(MainCamera);
    window.setKeyRepeatEnabled(true);
    window.setVerticalSyncEnabled(false);

    while (window.isOpen())
    {
        sf::Event event;
//        window.clear(sf::Color(42, 76, 61));
        window.clear(CurrentLevel->backgroundColor);

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