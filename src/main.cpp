// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <chrono>
#include "TileEntity.h"
#include "MapEditor.h"

int main(int argc, char **argv)
{
    std::cout << argv[0] << std::endl;
    MapEditor &Editor = MapEditor::Instance();
    Editor.ImageDirectory.clear();
    Editor.ImageDirectory.append(argv[0]);
    Editor.ImageDirectory = Editor.ImageDirectory.substr(0, Editor.ImageDirectory.size() - 11);
    Editor.ImageDirectory.append("Res/Images/");

    std::cout << Editor.ImageDirectory << std::endl;

    Editor.initWindow();

    return 0;
}