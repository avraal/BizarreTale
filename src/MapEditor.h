//
// Created by andrew on 03.04.18.
//

#ifndef BIZARRETALE_MAPEDITOR_H
#define BIZARRETALE_MAPEDITOR_H

#include <string>
#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <TGUI/Widgets/Scrollbar.hpp>
#include "MapEntity.h"

class MapEditor
{
private:
    MapEditor() {}
    ~MapEditor() {}
    std::vector<std::shared_ptr<MapEntity>> ObjList;
    sf::RenderWindow window;

    int prevScrollBarValue = 0;

public:
    MapEditor(MapEditor const&) = delete;
    MapEditor &operator=(MapEditor const&) = delete;
    static MapEditor& Instance()
    {
        static MapEditor e;
        return e;
    }

    bool initWindow();
    void display();
};

#endif //BIZARRETALE_MAPEDITOR_H
