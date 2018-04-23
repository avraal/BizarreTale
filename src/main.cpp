#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <chrono>
#include "MapEntity.h"
#include "MapEditor.h"
#include "ClassAnalizer.h"

int main(int argc, char **argv)
{
    std::cout << argv[0] << std::endl;
    MapEditor &Editor = MapEditor::Instance();
    Editor.CurrentDirectory.clear();
    Editor.CurrentDirectory.append(argv[0]);
    Editor.CurrentDirectory = Editor.CurrentDirectory.substr(0, Editor.CurrentDirectory.size() - 11);

    Editor.initWindow();

    ClassAnalizer &ca = ClassAnalizer::Instance();
    ca.start();


    return 0;
}