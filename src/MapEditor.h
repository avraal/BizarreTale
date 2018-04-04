//
// Created by andrew on 03.04.18.
//

#ifndef BIZARRETALE_MAPEDITOR_H
#define BIZARRETALE_MAPEDITOR_H

#include <string>
#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <TGUI/Widgets/Scrollbar.hpp>
#include <dirent.h>
#include "MapEntity.h"

class MapEditor
{
private:
    MapEditor()
    {
        ImagesFormats.push_back(".png");
        ImagesFormats.push_back(".jpg");
    }
    ~MapEditor() {}
    std::vector<std::shared_ptr<MapEntity>> ObjList;
    std::vector<std::string> PathToImages;
    std::vector<std::string> ImagesFormats;
    sf::RenderWindow window;
    void findAllFiles(std::vector<std::string> &Container, std::vector<std::string> FileFormats);


public:
    MapEditor(MapEditor const&) = delete;
    MapEditor &operator=(MapEditor const&) = delete;
    static MapEditor& Instance()
    {
        static MapEditor e;
        return e;
    }

    bool initWindow();
    std::string CurrentDirectory = "";
    void display();
};
#endif //BIZARRETALE_MAPEDITOR_H
