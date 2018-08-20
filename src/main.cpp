// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <chrono>
#include "Game/Game.hpp"
#include "Engine/Components/CTile.h"
#include "Engine/MapEditor.h"


int main(int argc, char **argv)
{
    Game game("Bizarre Tale");
    game.ImageDirectory.clear();
    game.ImageDirectory.append(argv[0]);
    game.ImageDirectory = game.ImageDirectory.substr(0, game.ImageDirectory.size() - 11);
    game.ImageDirectory.append("Res/Images/");
    if (!game.start())
    {
        return 1;
    }
    return 0;
}