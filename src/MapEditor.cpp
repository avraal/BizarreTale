//
// Created by andrew on 03.04.18.
//

#include "MapEditor.h"

bool MapEditor::initWindow()
{
    window.create(sf::VideoMode(1280, 720), "Hello, SFML"/*, sf::Style::Titlebar | sf::Style::Close*/);

    tgui::Gui gui{window};
    tgui::Theme theme{"tgui_themes/Black.txt"};

    auto scrollPanel = tgui::ScrollablePanel::create({"20%", "80%"});
    auto grid = tgui::Grid::create();
    scrollPanel->setPosition(10, 10);
    grid->setPosition(20, 20);
    scrollPanel->getRenderer()->setBackgroundColor(sf::Color(0, 0, 0, 128));
    uint x = 0, y = 0;
    for(uint i = 0; i < 15; i++, y++)
    {
        auto pic = tgui::Picture::create("1.png");
        if(y == 2)
        {
            x++;
            y = 0;
        }
        grid->addWidget(pic, x, y, {10, 10, 10, 10});
    }

    scrollPanel->setHorizontalScrollbarPolicy(tgui::ScrollablePanel::ScrollbarPolicy::Never);
    scrollPanel->add(grid);
    gui.add(scrollPanel);
    window.setVerticalSyncEnabled(true);

    findAllFiles();

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
                if (event.mouseButton.button == sf::Mouse::Right)
                {
                    window.create(sf::VideoMode(720, 480), "");
                }
                if (event.mouseButton.button == sf::Mouse::Left)
                {
//                    ObjList.push_back(std::move(std::shared_ptr<MapEntity>(
//                            new MapEntity("1.png", event.mouseButton.x, event.mouseButton.y))));

                }
            }
            gui.handleEvent(event);
        }
        gui.draw();
        for (auto o : ObjList)
        {
            window.draw(*o);
            std::cout << ObjList.size() << std::endl;
        }
        window.display();
    }
    return true;
}
void MapEditor::findAllFiles()
{
    std::cout << "findAllFiles" << std::endl;
    DIR *dir;
    dirent *directory;

    std::cout << "find in " << MapEditor::CurrentDirectory << std::endl;
    if((dir = opendir(MapEditor::CurrentDirectory.c_str())) != NULL)
    {
        std::cout << "find..." << std::endl;
        while((directory = readdir(dir)) != NULL)
        {
            char *last = strrchr(directory->d_name, '.');
            if(last != NULL)
            {
                //std::cout << MapEditor::CurrentDirectory << directory->d_name << std::endl;
                std::cout << last << std::endl;
                if (strcmp(last, ".png") == 0)
                {
                    std::cout << MapEditor::CurrentDirectory << directory->d_name << " added to stack" << std::endl;
                    PathToImages.push_back(MapEditor::CurrentDirectory.append(directory->d_name));
                }
            }
        }
        closedir(dir);
    } else
    {
        std::cerr << "Cant open a dir" << std::endl;
    }
    for(auto p : PathToImages)
    {
        std::cout << p << std::endl;
    }
}
