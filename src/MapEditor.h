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
#include "CTile.h"
#include "MapIO.h"
#include "CONST_DEFINITIONS.h"
#include "CPrimitiveQuad.hpp"
#include "Level.hpp"
#include "Systems/SLevelManager.hpp"

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
        delete CurrentLevel;
        delete levelManager;
    }
    std::vector<IEntity*> *LevelObjects;
    Level *CurrentLevel;                                   //container for all object on CurrentLevel
    SLevelManager *levelManager;
    std::vector<CPrimitiveQuad*> TileMap;           //draw grid for add new objects
    std::vector<std::string> PathToImages;                          //all images
    std::vector<std::string> ImagesFormats;                         //all supported image formats
    std::vector<std::pair<sf::Vertex, sf::Vertex>> LineGrid;        //grid of lines
    std::string CurrentPathFile;                                    //path to image, which added to map
    sf::RenderWindow window;                                        //main window
    sf::View MainCamera;                                            //main camera
    sf::Clock clock;
    //-------------------------------
    tgui::Panel::Ptr                objectProperties;

    tgui::Label::Ptr                objPropName;
    tgui::Label::Ptr                objPositionLabel;
    tgui::Label::Ptr                objPositionLabelX;
    tgui::Label::Ptr                objPositionLabelY;
    tgui::Label::Ptr                objIndexLabel;
    tgui::EditBox::Ptr              objIndexEditBox;
    tgui::EditBox::Ptr              objPropChangeNameBox;
    tgui::EditBox::Ptr              objPositionX;
    tgui::EditBox::Ptr              objPositionY;
    tgui::ScrollablePanel::Ptr      scrollProperties;
    tgui::Button::Ptr               objConfirmChanges;

    tgui::ScrollablePanel::Ptr scrollPanel;                         //panel with images

    tgui::Label::Ptr infoObjCountLabel;                             //show count of objects
    tgui::Label::Ptr infoFPSLabel;                                  //show current Framerate-Per-Second
    tgui::Panel::Ptr infoPanel;                                     //TODO: ?
    //-------------------------------

    tgui::ListBox::Ptr ObjectListBox;

    bool showInfo;
    bool canScroll;
    float CameraSpeed;

    MapIO &mio = MapIO::Instance();

    enum class EditorMode {ADD, SELECT, MULTISELECT};

    EditorMode CurrentMode;

    std::mutex b_mutex;
    EObject *SelectedEntity;
    std::set<EObject*> SelectedEntities;

    void drawTileMap(float size_x, float size_y);
    void findAllFiles(std::vector<std::string> &Container, std::vector<std::string> FileFormats);
    void SelectImage(const std::string &imagePath);
    void MouseCallbacks(sf::Event event);
    void KeyBoardCallbacks(sf::Event event);
    void ZoomViewAt(sf::Vector2i pixel, float zoom);
    void addInfoToPropertiesPanel();
    void UpdateObjectFromProperties();
    void LoadUI();
    void sortObjects();
    EObject *findEntityByName(const std::string &ObjName);

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
