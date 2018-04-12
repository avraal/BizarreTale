#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <chrono>
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

    std::ofstream toFile("Info.dat", std::ios_base::app);
    auto time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    if(!toFile)
    {
        std::cerr << "[Main] File not found" << std::endl;
    }
    else
    {
        toFile << "Date: "      << std::ctime(&time)             << std::endl;
        toFile << "MapEntity: " << sizeof(MapEntity) << " bytes" << std::endl;
        toFile << "MapEditor: " << sizeof(MapEditor) << " bytes" << std::endl;
        toFile << "--------------------------------------------" << std::endl;
    }

    toFile.close();
    return 0;
}