//// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
////
//// Created by andrew on 03.04.18.
////
//
//#ifndef DEMIURGE_MAPEDITOR_HPP
//#define DEMIURGE_MAPEDITOR_HPP
//
//#include <SFML/Graphics.hpp>
//#include <TGUI/TGUI.hpp>
//#include <TGUI/Widgets/Scrollbar.hpp>
//#include <dirent.h>
//#include <string>
//#include <mutex>
//#include <set>
//#include <nfd.h>
//#include "CONST_DEFINITIONS.hpp"
//#include "Level.hpp"
//#include "Systems/LevelManager.hpp"
//#include "CustomGUI/EditboxAndLabel.hpp"
//
//class EObject;
//class MapEditor : public Level
//{
//private:
////    std::vector<CPrimitiveQuad*> TileMap;                           //draw grid for add new objects
//    std::vector<std::string> PathToImages;                          //all images
//    std::vector<std::string> ImagesFormats;                         //all supported image formats
//    std::vector<std::pair<sf::Vertex, sf::Vertex>> LineGrid;        //grid of lines
//    std::string CurrentPathFile;                                    //path to image, which added to map
//    sf::Clock clock;
//    //------------------------------UI------------------------------
//        //-------------------Object properties----------------------
//            tgui::Panel::Ptr                objectProperties;
//            tgui::Label::Ptr                objPositionLabel;
//            tgui::EditboxAndLabel::Ptr      objIndexEdit;
//            tgui::EditboxAndLabel::Ptr      objPropChangeNameBox;
//            tgui::EditboxAndLabel::Ptr      objPositionX;
//            tgui::EditboxAndLabel::Ptr      objPositionY;
//            tgui::ScrollablePanel::Ptr      scrollProperties;
//            tgui::Button::Ptr               objConfirmChanges;
//        //--------------------Object properties---------------------
//
//        //-------------------------Info-----------------------------
//            tgui::Panel::Ptr infoPanel;
//            tgui::Label::Ptr infoObjCountLabel;
//            tgui::Label::Ptr infoObjReferenceCount;
//            tgui::Label::Ptr infoDrawableObjCountLabel;
//            tgui::Label::Ptr infoDrawableReferenceCount;
//            tgui::Label::Ptr infoFPSLabel;
//        //-------------------------Info-----------------------------
//
//        tgui::ScrollablePanel::Ptr scrollPanel;
//        tgui::ListBox::Ptr ObjectListBox;
//        tgui::ChildWindow::Ptr selectComponentWindow;
//    //------------------------------UI------------------------------
//
//    bool showInfo;
//    bool canScroll;
//    bool canCreateOrEdit;
//    float CameraSpeed;
//
//    enum class EditorMode {ADD, SELECT, MULTISELECT};
//    enum class ComponentsName {TILE};
//
//    EditorMode CurrentMode;
//
//    std::mutex b_mutex;
////    std::shared_ptr<IEntity> SelectedEntity;
//    std::map<us_int, std::shared_ptr<IEntity>> SelectedEntities;
//
//private:
//    void drawTileMap(float size_x, float size_y);
////    bool findAllFiles(std::vector<std::string> &Container, std::vector<std::string> FileFormats);
//    void SelectImage(const std::string &imagePath);
//    virtual void MouseCallbacks(sf::RenderWindow &window, sf::Event &event);
//    virtual void KeyBoardCallbacks(sf::RenderWindow &window, sf::Event &event);
//    void ZoomViewAt(sf::RenderWindow &window, sf::Vector2i pixel, float zoom);
//    void ClearObjectProperties();
//    void addInfoToPropertiesPanel();
//    void AddComponentToObject(std::shared_ptr<IEntity> e, int pos_x, int pos_y);
//    void UpdateObjectFromProperties();
//    void AddToSelectedEntities(std::shared_ptr<IEntity> ie);
//
//protected:
//    virtual void loadGui(sf::RenderWindow &window);
//
//public:
//    MapEditor(const std::string &Name);
//    virtual ~MapEditor() {}
//    virtual void draw(sf::RenderWindow &window) override;
//
//    virtual bool prepareLevel(sf::RenderWindow &window) override;
//};
//#endif //DEMIURGE_MAPEDITOR_HPP
