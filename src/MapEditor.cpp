//
// Created by andrew on 03.04.18.
//

#include "MapEditor.h"

bool MapEditor::initWindow()
{
    showInfo = true;
    float lastTime = 0;
    window.create(sf::VideoMode(WINDOW_SIZE_HD_WIDTH, WINDOW_SIZE_HD_HEIGHT),
                  "Bizarre Tale: Map Editor"/*, sf::Style::Titlebar | sf::Style::Close*/);
    MainCamera = window.getView();
    MainCamera.setCenter(300, 320);
    findAllFiles(PathToImages, ImagesFormats);
    drawTileMap();
    tgui::Gui gui{window};
    tgui::Theme theme{"tgui_themes/Black.txt"};

    scrollPanel = tgui::ScrollablePanel::create({"20%", "100%"});
    auto grid = tgui::Grid::create();
    scrollPanel->setPosition(0, 0);
    grid->setPosition(20, 20);
    scrollPanel->getRenderer()->setBackgroundColor(sf::Color(0, 0, 0, 128));

    uint x = 0, y = 0;
    for (auto i : PathToImages)
    {
        auto pic = tgui::Picture::create(i);
        pic->connect(pic->onClick.getName(), &MapEditor::AddObject, this, i);
        if (y == 2)
        {
            x++;
            y = 0;
        }
        y++;
        grid->addWidget(pic, x, y, {10, 10, 10, 10});
    }

    scrollPanel->setHorizontalScrollbarPolicy(tgui::ScrollablePanel::ScrollbarPolicy::Never);
    scrollPanel->add(grid);

    infoPanel = tgui::Panel::create({200, "10%"});
    infoPanel->setPosition(window.getSize().x - infoPanel->getSize().x, 0);
    infoPanel->getRenderer()->setBackgroundColor(sf::Color(0, 0, 0, 128));

    infoObjCountLabel = tgui::Label::create();
    infoObjCountLabel->getRenderer()->setTextColor(sf::Color::White);
    infoObjCountLabel->setTextSize(12);

    infoFPSLabel = tgui::Label::create();
    infoFPSLabel->getRenderer()->setTextColor(sf::Color::White);
    infoFPSLabel->setTextSize(12);
    infoFPSLabel->setPosition(0, 14);
    infoPanel->add(infoObjCountLabel);
    infoPanel->add(infoFPSLabel);

    gui.add(infoPanel);
    gui.add(scrollPanel);

    window.setKeyRepeatEnabled(true);
    window.setVerticalSyncEnabled(true);
    while (window.isOpen())
    {
        float currentTime = clock.restart().asSeconds();
        float fps = 1.f / currentTime;
        lastTime = currentTime;
        sf::Event event;
        window.clear(sf::Color(42, 76, 61));

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            //            if (event.type == sf::Event::Resized)
            //            {
            //                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
            //                window.setView(sf::View(visibleArea));
            //            }
            MouseCallbacks(event);
            KeyBoardCallbacks(event);
            gui.handleEvent(event);
        }

        window.setView(MainCamera);

        for (auto t : TileMap)
        {
            window.draw(*t);
        }
        for (auto o : ObjList)
        {
            window.draw(*o);
        }
        infoObjCountLabel->setText("Object count: " + std::to_string(ObjList.size()));
        infoFPSLabel->setText("FPS: " + std::to_string((int)fps));
        gui.draw();
        window.display();
    }
    return true;
}

void MapEditor::findAllFiles(std::vector<std::string> &Container, std::vector<std::string> FileFormats)
{
    DIR *dir;
    dirent *directory;
    if ((dir = opendir(MapEditor::CurrentDirectory.c_str())) != NULL)
    {
        while ((directory = readdir(dir)) != NULL)
        {
            char *last = strrchr(directory->d_name, '.');
            if (last != NULL)
            {
                for (auto f : FileFormats)
                {
                    if (strcmp(last, f.c_str()) == 0)
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
void MapEditor::AddObject(std::string imagePath)
{
    CurrentPathFile = imagePath;
}
void MapEditor::drawTileMap()
{
    int height = 10;
    int width = 10;
    std::vector<std::string> Tiles;
    std::vector<std::string> Formats;
    Formats.push_back(".png");
    findAllFiles(Tiles, Formats);
    //added tiles
    for (uint i = 1; i <= height * width; i++)
    {
        TileMap.push_back(std::move(std::shared_ptr<MapEntity>(
                new MapEntity("", {.0f, .0f}))));
    }
    //set position
    uint x = 0, y = 0;
    for (auto t : TileMap)
    {
        t->setPosition(x * (TILE_SIZE_DEFAULT + 1), y * (TILE_SIZE_DEFAULT + 1));

        x++;
        if (x == width)
        {
            y++;
            x = 0;
        }
    }
}
void MapEditor::MouseCallbacks(sf::Event event)
{
    if (event.type == sf::Event::MouseWheelScrolled)
    {
        if (event.mouseWheelScroll.delta > 0)
        {
            ZoomViewAt({event.mouseWheelScroll.x, event.mouseWheelScroll.y}, (1.f / 1.1f));
        } else if (event.mouseWheelScroll.delta < 0)
        {
            ZoomViewAt({event.mouseWheelScroll.x, event.mouseWheelScroll.y}, 1.1f);
        }
    }

    if (event.type == sf::Event::MouseButtonPressed)
    {
        if (event.mouseButton.button == sf::Mouse::Right)
        {
            sf::Vector2i Mouse = sf::Mouse::getPosition(window);
            float w = window.mapPixelToCoords(Mouse).x;
            float h = window.mapPixelToCoords(Mouse).y;
            MainCamera.setCenter(w, h);
        }

        if (event.mouseButton.button == sf::Mouse::Left &&
            !scrollPanel->mouseOnWidget(tgui::Vector2f(event.mouseButton.x, event.mouseButton.y)))
        {
            for (auto t : TileMap)
            {
                if (!CurrentPathFile.empty())
                {
                    sf::Vector2f MglobalPosition{window.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y})};
                    if (MglobalPosition.x > t->getPosition().x && MglobalPosition.y > t->getPosition().y
                        && MglobalPosition.x < t->getPosition().x + t->getSize().x
                        && MglobalPosition.y < t->getPosition().y + t->getSize().y)
                    {
                        for (auto o : ObjList)
                        {
                            if (o != nullptr)
                            {
                                if (t->getPosition() == o->getPosition())
                                {
                                    auto it = std::find(ObjList.begin(), ObjList.end(), o);
                                    if (it != ObjList.end())
                                    {
                                        ObjList.erase(it);
                                    }
                                }
                            }
                        }
                        ObjList.push_back(std::move(std::shared_ptr<MapEntity>(
                                new MapEntity(CurrentPathFile, {t->getPosition().x, t->getPosition().y}))));
                    }
                } else
                {
                    std::cout << "[WARNING | MapEditor]: Current Path File is empty" << std::endl;
                }
            }
        }
    }
}
void MapEditor::ZoomViewAt(sf::Vector2i pixel, float zoom)
{
    const sf::Vector2f beforeCoord{window.mapPixelToCoords(pixel)};
    MainCamera.zoom(zoom);
    const sf::Vector2f afterCoord{window.mapPixelToCoords(pixel)};
    const sf::Vector2f offsetCoords{beforeCoord - afterCoord};
    MainCamera.move(offsetCoords);
}
void MapEditor::KeyBoardCallbacks(sf::Event event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Escape)
        {
            window.close();
        }
        switch (event.key.code)
        {
            case sf::Keyboard::Right:
            {
                MainCamera.move(CameraSpeed, 0.0f);
                break;
            }
            case sf::Keyboard::Left:
            {
                MainCamera.move(-CameraSpeed, 0.0f);
                break;
            }
            case sf::Keyboard::Up:
            {
                MainCamera.move(0.0f, -CameraSpeed);
                break;
            }
            case sf::Keyboard::Down:
            {
                MainCamera.move(0.0f, CameraSpeed);
                break;
            }
            case sf::Keyboard::F3:
            {
                showInfo = !showInfo;
                if(showInfo)
                {
                    infoPanel->show();
                } else
                {
                    infoPanel->hide();
                }
                break;
            }
        }
    }
}
