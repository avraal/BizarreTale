// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

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
#include <string>
#include <mutex>
#include "TileEntity.h"
#include "MapIO.h"
#include "CONST_DEFINITIONS.h"
#include "PrimitiveQuad.hpp"

class MapEditor
{
private:
    MapEditor()
    {
        ImageDirectory = "";
        CurrentPathFile  = "";
        ImagesFormats.push_back(".png");
        ImagesFormats.push_back(".jpg");
        CameraSpeed = 4.0f;
        showInfo = true;
        canScroled = true;
        CurrentMode = EditorMode::EDIT;
    }
    ~MapEditor()
    {
    }
    std::list<std::shared_ptr<TileEntity>> ObjList;
    std::list<std::shared_ptr<PrimitiveQuad>> TileMap;
    std::vector<std::string> PathToImages;
    std::vector<std::string> ImagesFormats;
    std::string CurrentPathFile;
    sf::RenderWindow window;
    sf::View MainCamera;
    sf::Clock clock;
    tgui::ScrollablePanel::Ptr scrollPanel;
    tgui::Label::Ptr infoObjCountLabel;
    tgui::Label::Ptr infoFPSLabel;
    tgui::Panel::Ptr infoPanel;
    tgui::ListBox::Ptr ObjectListBox;

    bool showInfo;
    bool canScroled;
    float CameraSpeed;

    MapIO &mio = MapIO::Instance();

    enum EditorMode {ADD, EDIT};

    EditorMode CurrentMode;

    std::mutex b_mutex;

    void drawTileMap(float size_x, float size_y);
    void findAllFiles(std::vector<std::string> &Container, std::vector<std::string> FileFormats);
    void SelectImage(std::string imagePath);
    void MouseCallbacks(sf::Event event);
    void KeyBoardCallbacks(sf::Event event);
    void ZoomViewAt(sf::Vector2i pixel, float zoom);
    void ChangeScrollablePanelStatus(bool val);

public:
    MapEditor(MapEditor const&) = delete;
    MapEditor &operator=(MapEditor const&) = delete;
    static MapEditor& Instance()
    {
        static MapEditor e;
        return e;
    }

    bool initWindow();
    std::string ImageDirectory;
    std::string LuaDirectory;

    void SaveToFile(std::string fileName, std::list<std::shared_ptr<TileEntity>> obj);
    void LoadFromFile(std::string fileName, std::list<std::shared_ptr<TileEntity>> &obj);
};
#endif //BIZARRETALE_MAPEDITOR_H
