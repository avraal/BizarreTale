#include <iostream>
#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>

#include "MapEntity.h"
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

void Some(const std::string path, std::vector<MapEntity> &ObjList)
{
    std::cout << path << std::endl;
    ObjList.push_back(MapEntity("1.png", 300.f, 300.f));
}

int main(int argc, char **argv)
{
    std::cout << argv[0] << std::endl;
    std::vector<MapEntity> ObjList;

    sf::RenderWindow window(sf::VideoMode(1280, 720), "Hello, SFML", sf::Style::Titlebar | sf::Style::Close);
    tgui::Gui gui{window};
    auto tabs = tgui::Tab::create();
    tabs->add("first");
    tabs->add("second");
    tabs->setPosition(20, 20);
    gui.add(tabs);
    auto panel1 = tgui::Panel::create();
    panel1->setSize(400, 300);
    panel1->setPosition(tabs->getPosition().x, tabs->getPosition().y + tabs->getTabHeight());
    gui.add(panel1, "FirstPanel");
    auto panel2 = tgui::Panel::copy(panel1);
    gui.add(panel2, "SecondPanel");

    auto pic1 = tgui::Picture::create("1.png");
    pic1->connect("clicked", Some, pic1->getLoadedFilename(), std::ref(ObjList));
    panel1->add(pic1);
    //    panel2->add(tgui::Picture::create("1.png"));

    tabs->connect("TabSelected", onTabSelected, std::ref(gui));

    tabs->select("first");
    panel1->show();
    panel2->hide();
    window.setVerticalSyncEnabled(true);

    while (window.isOpen())
    {
        sf::Event event;
        window.clear(sf::Color(42, 76, 61));

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
//                    ObjList.push_back(MapEntity("1.png", event.mouseButton.x, event.mouseButton.y));
                }
            }
            gui.handleEvent(event);
        }
        gui.draw();
        for (auto o : ObjList)
        {
            window.draw(o);
            
            std::cout << ObjList.size() << std::endl;
        }
        window.display();
    }
    return 0;
}