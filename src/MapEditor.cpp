
// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// Created by andrew on 03.04.18.
//

#include <thread>
#include "MapEditor.h"

bool MapEditor::initWindow()
{
    window.create(sf::VideoMode(WINDOW_SIZE_HD_WIDTH, WINDOW_SIZE_HD_HEIGHT),
                  "Bizarre Tale: Map Editor"/*, sf::Style::Titlebar | sf::Style::Close*/);
    MainCamera = window.getView();
    MainCamera.setCenter(300, 320);
    findAllFiles(PathToImages, ImagesFormats);
    drawTileMap();
    tgui::Gui gui{window};
    tgui::Theme theme{"tgui_themes/Black.txt"};

    scrollPanel = tgui::ScrollablePanel::create({"100%", "25%"});
    auto grid = tgui::Grid::create();
    scrollPanel->setPosition(0, window.getSize().y - (window.getSize().y * 25 / 100));
    grid->setPosition(20, 20);
    scrollPanel->getRenderer()->setBackgroundColor(sf::Color(0, 0, 0, 225));

    uint x = 0, y = 0;
    for (auto i : PathToImages)
    {
        auto pic = tgui::Picture::create(i);
        pic->connect(pic->onClick.getName(), &MapEditor::SelectImage, this, i);
        if (y == 14)
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
    infoObjCountLabel->setTextSize(INFO_PANEL_TEXT_SIZE);

    infoFPSLabel = tgui::Label::create();
    infoFPSLabel->getRenderer()->setTextColor(sf::Color::White);
    infoFPSLabel->setTextSize(INFO_PANEL_TEXT_SIZE);
    infoFPSLabel->setPosition(0, INFO_PANEL_TEXT_SIZE + 2);
    infoPanel->add(infoObjCountLabel);
    infoPanel->add(infoFPSLabel);

    gui.add(infoPanel);
    gui.add(scrollPanel);

    scrollPanel->connect(scrollPanel->onMouseLeave.getName(), &MapEditor::ChangeScrollablePanelStatus, this, true);
    scrollPanel->connect(scrollPanel->onMouseEnter.getName(), &MapEditor::ChangeScrollablePanelStatus, this, false);

    window.setKeyRepeatEnabled(true);
    window.setVerticalSyncEnabled(true);
    while (window.isOpen())
    {
        float currentTime = clock.restart().asSeconds();
        float fps = 1.f / currentTime;
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
        infoFPSLabel->setText("FPS: " + std::to_string((int) fps));
        gui.draw();
        window.display();
    }
    return true;
}

void MapEditor::findAllFiles(std::vector<std::string> &Container, std::vector<std::string> FileFormats)
{
    DIR *dir;
    dirent *directory;
    if(FileFormats.empty())
    {
        FileFormats.push_back(".*");
    }
    if ((dir = opendir(MapEditor::ImageDirectory.c_str())) != NULL)
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
                        std::cout << MapEditor::ImageDirectory << directory->d_name << " added to stack" << std::endl;
                        Container.push_back(MapEditor::ImageDirectory + directory->d_name);
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
void MapEditor::SelectImage(std::string imagePath)
{
    CurrentPathFile = imagePath;
    CurrentMode = EditorMode::ADD;
    std::cout << "Prepare to add object" << std::endl;
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
        if (canScroled)
        {
            if (event.mouseWheelScroll.delta > 0)
            {
                ZoomViewAt({event.mouseWheelScroll.x, event.mouseWheelScroll.y}, (1.f / 1.1f));
            } else if (event.mouseWheelScroll.delta < 0)
            {
                ZoomViewAt({event.mouseWheelScroll.x, event.mouseWheelScroll.y}, 1.1f);
            }
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
                sf::Vector2f MouseglobalPosition{window.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y})};
                bool clickCondition =
                        MouseglobalPosition.x > t->getPosition().x && MouseglobalPosition.y > t->getPosition().y
                        && MouseglobalPosition.x < t->getPosition().x + t->getSize().x
                        && MouseglobalPosition.y < t->getPosition().y + t->getSize().y;
                if (clickCondition)
                {
                    std::cout << "Current mode = " << CurrentMode << std::endl;
                    switch (CurrentMode)
                    {
                        case EditorMode::ADD:
                        {
                            ObjList.push_back(std::move(std::shared_ptr<MapEntity>(
                                    new MapEntity(CurrentPathFile.c_str(), {t->getPosition().x, t->getPosition().y}))));
                            break;
                        }
                        case EditorMode::EDIT:
                        {
                            for (auto o : ObjList)
                            {
                                if (o != nullptr)
                                {
                                    if (t->getPosition() == o->getPosition())
                                    {
                                        std::cout << "Edit x:" << o->getPosition().x << " y:" << o->getPosition().y
                                                  << " object" << std::endl;
                                    }
                                }
                            }
                            break;
                        }
                    }
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
    const sf::Vector2f offsetCoord{beforeCoord - afterCoord};
    MainCamera.move(offsetCoord);
}
void MapEditor::KeyBoardCallbacks(sf::Event event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        switch (event.key.code)
        {
            case sf::Keyboard::E:
            {
                CurrentMode = EditorMode::EDIT;
                std::cout << "Edit mode enabled" << std::endl;
                break;
            }
            case sf::Keyboard::Escape:
            {
                window.close();
            }
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
                infoPanel->setVisible(showInfo);
                break;
            }
            case sf::Keyboard::Space:
            {
                std::thread thr(&MapEditor::SaveToFile, this, "test.mio", ObjList);
                thr.join();
                break;
            }
            case sf::Keyboard::LControl:
            {
                std::thread thr(&MapEditor::LoadFromFile, this, "test.mio", std::ref(ObjList));
                thr.join();
                break;
            }
        }
    }
}
void MapEditor::ChangeScrollablePanelStatus(bool val)
{
    canScroled = val;
}
void MapEditor::LoadFromFile(std::string fileName, std::list<std::shared_ptr<MapEntity>> &obj)
{
    mio.LoadFromFile(fileName, obj);
}
void MapEditor::SaveToFile(std::string fileName, std::list<std::shared_ptr<MapEntity>> obj)
{
    mio.SaveToFile(fileName, obj);
}
