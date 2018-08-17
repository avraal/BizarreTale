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
#include <set>
#include "Components/CTile.h"
#include "MapIO.h"
#include "CONST_DEFINITIONS.h"
#include "Components/CPrimitiveQuad.hpp"
#include "Level.hpp"
#include "Systems/SLevelManager.hpp"
#include "CustomGUI/EditboxAndLabel.hpp"

class EObject;
class MapEditor final
{
private:
    MapEditor() noexcept
    {
        ImageDirectory = "";
        CurrentPathFile  = "";
        ImagesFormats.push_back(".png");
        ImagesFormats.push_back(".jpg");
        CameraSpeed = 4.0f;
        showInfo = true;
        canScroll = true;
        CurrentMode = EditorMode::SELECT;
        SelectedEntity = nullptr;
    }
    virtual ~MapEditor()
    {
    }

    std::vector<std::shared_ptr<IEntity>> *LevelObjects;
    std::shared_ptr<Level> CurrentLevel;                                            //container for all object on CurrentLevel
    std::unique_ptr<SLevelManager> levelManager;
    std::vector<CPrimitiveQuad*> TileMap;                           //draw grid for add new objects
    std::vector<std::string> PathToImages;                          //all images
    std::vector<std::string> ImagesFormats;                         //all supported image formats
    std::vector<std::pair<sf::Vertex, sf::Vertex>> LineGrid;        //grid of lines
    std::string CurrentPathFile;                                    //path to image, which added to map
    sf::RenderWindow window;                                        //main window
    sf::View MainCamera;                                            //main camera
    sf::Clock clock;
    //------------------------------UI------------------------------
        //-------------------Object properties----------------------
            tgui::Panel::Ptr                objectProperties;
            tgui::Label::Ptr                objPositionLabel;
            tgui::EditboxAndLabel::Ptr      objIndexEdit;
            tgui::EditboxAndLabel::Ptr      objPropChangeNameBox;
            tgui::EditboxAndLabel::Ptr      objPositionX;
            tgui::EditboxAndLabel::Ptr      objPositionY;
            tgui::ScrollablePanel::Ptr      scrollProperties;
            tgui::Button::Ptr               objConfirmChanges;
        //--------------------Object properties---------------------

        //--------------------------Info----------------------------
            tgui::Panel::Ptr infoPanel;
            tgui::Label::Ptr infoObjCountLabel;
            tgui::Label::Ptr infoFPSLabel;
        //--------------------------Info----------------------------

        tgui::ScrollablePanel::Ptr scrollPanel;
    //------------------------------UI------------------------------

    tgui::ListBox::Ptr ObjectListBox;

    bool showInfo;
    bool canScroll;
    float CameraSpeed;

    MapIO &mio = MapIO::Instance();

    enum class EditorMode {ADD, SELECT, MULTISELECT};

    EditorMode CurrentMode;

    std::mutex b_mutex;
    std::shared_ptr<IEntity> SelectedEntity;
    std::map<int, std::shared_ptr<IEntity>> SelectedEntities;

    void drawTileMap(float size_x, float size_y);
    void findAllFiles(std::vector<std::string> &Container, std::vector<std::string> FileFormats);
    void SelectImage(const std::string &imagePath);
    void MouseCallbacks(sf::Event event);
    void KeyBoardCallbacks(sf::Event event);
    void ZoomViewAt(sf::Vector2i pixel, float zoom);
    void releaseSelectEntity();
    void addInfoToPropertiesPanel();
    void UpdateObjectFromProperties();
    void LoadUI();

public:
    MapEditor(MapEditor const&) = delete;
    MapEditor(MapEditor&&) = delete;
    MapEditor &operator=(MapEditor const&) = delete;
    MapEditor &operator=(MapEditor&&) = delete;

    static MapEditor &Instance()
    {
        static MapEditor *me = new MapEditor();
        return *me;
    }

    bool initWindow();

    std::string ImageDirectory;
//    void SaveToFile(std::string fileName, std::vector<std::shared_ptr<CTile>> obj);
//    void LoadFromFile(std::string fileName, std::vector<std::shared_ptr<CTile>> &obj);
};
#endif //BIZARRETALE_MAPEDITOR_H
