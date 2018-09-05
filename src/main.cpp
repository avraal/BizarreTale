// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifdef __linux__
#define OS "LINUX"
#else
#define OS "UNSUPPORTED OS"
#endif

#include <iostream>
#include <TGUI/TGUI.hpp>
#include "Game/Game.hpp"
#include "Engine/Components/CTile.h"
#include "Engine/MapEditor.h"

bool prepare();

int main(int argc, char **argv)
{
    if (!prepare())
    {
        return 1;
    }
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

bool prepare()
{
    std::cout << OS << std::endl;
    return strcmp(OS, "UNSUPPORTED OS");
//    return OS != "UNSUPPORTED OS";
}