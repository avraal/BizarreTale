
// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by Andrew Volski on 20.08.18.
//

#ifndef BIZARRETALE_GAME_HPP
#define BIZARRETALE_GAME_HPP

#include <string>
#include <SFML/Graphics/RenderWindow.hpp>

class Game final
{
private:
    sf::RenderWindow window;
    sf::View MainCamera;
public:
    Game(const std::string title);
};

#endif //BIZARRETALE_GAME_HPP
