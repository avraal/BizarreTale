
// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by Andrew Volski on 20.08.18.
//

#ifndef DEMIURGE_GAME_HPP
#define DEMIURGE_GAME_HPP

#include <string>
#include <SFML/Graphics/RenderWindow.hpp>
#include "../Engine/Systems/LevelManager.hpp"

class Game final
{
private:
    sf::RenderWindow window;
    sf::View MainCamera;
    std::string Title;

    std::unique_ptr<LevelManager> levelManager;
    std::shared_ptr<Level> CurrentLevel;
    std::vector<std::string> PathToImages;                          //all images
    std::vector<std::string> ImagesFormats;                         //all supported image formats

public:
    Game(const std::string &title);
    bool start();
    std::string ImageDirectory;

};

#endif //DEMIURGE_GAME_HPP
