
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
    std::shared_ptr<MapEditor> editor = std::make_shared<MapEditor>(0, "MapEditor"); //ToDo: Add generate ID for Level's
    levelManager->registerLevel(editor);
}

bool Game::start()
{
    window.create(sf::VideoMode(WINDOW_SIZE_HD_WIDTH, WINDOW_SIZE_HD_HEIGHT), Title);
    MainCamera = window.getView();
    MainCamera.setCenter(300, 320);

    CurrentLevel = levelManager->loadLevel("MapEditor");
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

bool Game::findAllFiles(std::vector<std::string> &Container, std::vector<std::string> FileFormats)
{
    bool result = false;
    DIR *dir;
    dirent *directory;
    if (FileFormats.empty())
    {
        FileFormats.emplace_back(".*");
    }
    if ((dir = opendir(ImageDirectory.c_str())) != nullptr)
    {
        while ((directory = readdir(dir)) != nullptr)
        {
            char *last = strrchr(directory->d_name, '.');
            if (last != nullptr)
            {
                for (const auto &f : FileFormats)
                {
                    if (strcmp(last, f.c_str()) == 0)
                    {
                        std::cout << ImageDirectory << directory->d_name << " added to stack" << std::endl;
                        Container.push_back(ImageDirectory + directory->d_name);
                        result = true;
                    }
                }
            }
        }
        closedir(dir);
    } else
    {
        std::cerr << "Can't open a dir" << std::endl;
    }
    return result;
}

