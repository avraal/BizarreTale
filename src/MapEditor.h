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
        CurrentDirectory = "";
        CurrentPathFile  = "";
        ImagesFormats.push_back(".png");
        ImagesFormats.push_back(".jpg");
        CameraSpeed = 2.0f;
    }
    ~MapEditor() {}
    std::vector<std::shared_ptr<MapEntity>> ObjList;
    std::vector<std::string> PathToImages;
    std::vector<std::string> ImagesFormats;
    std::vector<std::shared_ptr<MapEntity>> TileMap;
    std::string CurrentPathFile;
    sf::RenderWindow window;
    sf::View MainCamera;
    tgui::ScrollablePanel::Ptr scrollPanel;

    float CameraSpeed;

    void drawTileMap();
    void findAllFiles(std::vector<std::string> &Container, std::vector<std::string> FileFormats);
    void AddObject(std::string imagePath);
    void MouseCallbacks(sf::Event event);
    void KeyBoardCallbacks(sf::Event event);
    void ZoomViewAt(sf::Vector2i pixel, float zoom);

public:
    MapEditor(MapEditor const&) = delete;
    MapEditor &operator=(MapEditor const&) = delete;
    static MapEditor& Instance()
    {
        static MapEditor e;
        return e;
    }

    bool initWindow();
    std::string CurrentDirectory;
};
#endif //BIZARRETALE_MAPEDITOR_H
