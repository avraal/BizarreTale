// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifdef __linux__
    #define OS "LINUX"
#elif __WIN32__
    #ifdef __WIN64__
        #define OS "WIN64"
    #else
        #define OS "WIN32"
    #endif
#else
    #define OS "UNSUPPORTED OS"
#endif

#include <iostream>
#include "Game/Game.hpp"

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
    game.ImageDirectory = game.ImageDirectory.substr(0, game.ImageDirectory.size() - 8);
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
}
