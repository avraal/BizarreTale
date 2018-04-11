#include <iostream>
#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include "MapEntity.h"
#include "MapEditor.h"

int main(int argc, char **argv)
{
    std::cout << argv[0] << std::endl;
    std::vector<std::shared_ptr<MapEntity>> ObjList;
    MapEditor &Editor = MapEditor::Instance();
    Editor.CurrentDirectory.clear();
    Editor.CurrentDirectory.append(argv[0]);
    Editor.CurrentDirectory = Editor.CurrentDirectory.substr(0, Editor.CurrentDirectory.size() - 11);

    Editor.initWindow();

    return 0;
}