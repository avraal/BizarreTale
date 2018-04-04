//
// Created by andrew on 03.04.18.
//

#include "MapEditor.h"

bool MapEditor::initWindow()
{
    window.create(sf::VideoMode(1280, 720), "Hello, SFML"/*, sf::Style::Titlebar | sf::Style::Close*/);
    findAllFiles(PathToImages, ImagesFormats);
    
    tgui::Gui gui{window};
    tgui::Theme theme{"tgui_themes/Black.txt"};

    auto scrollPanel = tgui::ScrollablePanel::create({"20%", "80%"});
    auto grid = tgui::Grid::create();
    scrollPanel->setPosition(10, 10);
    grid->setPosition(20, 20);
    scrollPanel->getRenderer()->setBackgroundColor(sf::Color(0, 0, 0, 128));

    uint x = 0, y = 0;
    for(auto i : PathToImages)
    {
        auto pic = tgui::Picture::create(i);
        if(y == 2)
        {
            x++;
            y = 0;
        }
        y++;
        grid->addWidget(pic, x, y, {10, 10, 10, 10});
    }

    scrollPanel->setHorizontalScrollbarPolicy(tgui::ScrollablePanel::ScrollbarPolicy::Never);
    scrollPanel->add(grid);
    gui.add(scrollPanel);
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

void MapEditor::findAllFiles(std::vector<std::string> &Container, std::vector<std::string> FileFormats)
{
    DIR *dir;
    dirent *directory;
    if((dir = opendir(MapEditor::CurrentDirectory.c_str())) != NULL)
    {
        while((directory = readdir(dir)) != NULL)
        {
            char *last = strrchr(directory->d_name, '.');
            if(last != NULL)
            {
                for(auto f : FileFormats)
                {
                    if(strcmp(last, f.c_str()) == 0)
                    {
                        std::cout << MapEditor::CurrentDirectory << directory->d_name << " added to stack" << std::endl;
                        Container.push_back(MapEditor::CurrentDirectory + directory->d_name);
                    }
                }
            }
        }
        closedir(dir);
    } else
    {
        std::cerr << "Cant open a dir" << std::endl;
    }
}
