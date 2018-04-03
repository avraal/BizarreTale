#include <iostream>
#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>

#include "MapEntity.h"
#include "MapEditor.h"
void onTabSelected(tgui::Gui &gui, std::string selectedTab)
{
    if (selectedTab == "first")
    {
        gui.get("FirstPanel")->show();
        gui.get("SecondPanel")->hide();
    } else if (selectedTab == "second")
    {
        gui.get("FirstPanel")->hide();
        gui.get("SecondPanel")->show();

    }
}

void Some(const std::string path, std::vector<std::shared_ptr<MapEntity>> &ObjList)
{
    std::cout << path << std::endl;
    ObjList.push_back(std::move(std::shared_ptr<MapEntity>(new MapEntity(path, 300.f, 300.f))));
}

int main(int argc, char **argv)
{
    std::cout << argv[0] << std::endl;
    std::vector<std::shared_ptr<MapEntity>> ObjList;
    MapEditor &Editor = MapEditor::Instance();
    Editor.initWindow();

    return 0;
}