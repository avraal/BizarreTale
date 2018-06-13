
// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// Created by andrew on 03.04.18.
//

#include <thread>
#include "MapEditor.h"
#include "PrimitiveQuad.hpp"

bool MapEditor::initWindow()
{
    window.create(sf::VideoMode(WINDOW_SIZE_HD_WIDTH, WINDOW_SIZE_HD_HEIGHT),
                  "Bizarre Tale: Map Editor"/*, sf::Style::Titlebar | sf::Style::Close*/);
    MainCamera = window.getView();
    MainCamera.setCenter(300, 320);
    findAllFiles(PathToImages, ImagesFormats);
    drawTileMap(TILE_SIZE_DEFAULT, TILE_SIZE_DEFAULT);
    tgui::Gui gui{window};
    tgui::Theme theme{"tgui_themes/Black.txt"};

    ObjectListBox = ::tgui::ListBox::create();
    ObjectListBox->getRenderer()->setBackgroundColor(sf::Color(16, 16, 16, 200));
    ObjectListBox->getRenderer()->setTextColor(sf::Color::White);
    ObjectListBox->setSize(250, window.getSize().y);
    ObjectListBox->setItemHeight(25);
    ObjectListBox->setPosition(0, 0);

    scrollPanel = tgui::ScrollablePanel::create({"100%", "25%"});
    auto grid = tgui::Grid::create();
    scrollPanel->setPosition(ObjectListBox->getSize().x, window.getSize().y - (window.getSize().y * 25 / 100));

    scrollPanel->setSize(window.getSize().x - ObjectListBox->getSize().x, 250);
    grid->setPosition(20, 20);

    scrollPanel->getRenderer()->setBackgroundColor(sf::Color(0, 0, 0, 225));
    auto imgInRow = scrollPanel->getSize().x / 64 - (PathToImages.size() * 0.25);
    std::cout << imgInRow << std::endl;
    uint x = 0, y = 0;
    for (auto i : PathToImages)
    {
        auto pic = tgui::Picture::create(i);
        pic->connect(pic->onClick.getName(), &MapEditor::SelectImage, this, i);
        if (y == ceil(imgInRow))
        {
            x++;
            y = 0;
        }
        y++;
        grid->addWidget(pic, x, y, {5, 5, 5, 5});
    }

    scrollPanel->setHorizontalScrollbarPolicy(tgui::ScrollablePanel::ScrollbarPolicy::Never);
    scrollPanel->setVerticalScrollbarPolicy(tgui::ScrollablePanel::ScrollbarPolicy::Always);
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
    gui.add(ObjectListBox);

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

        for(auto g : LineGrid)
        {
            sf::Vertex line[] =
                    {
                        g.first,
                        g.second
                    };
            window.draw(line, 2, sf::Lines);
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
    if (FileFormats.empty())
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
void MapEditor::drawTileMap(float size_x, float size_y)
{
    TileMap.clear();
    int height = 10;
    int width = 10;
    std::vector<std::string> Tiles;
    std::vector<std::string> Formats;
    Formats.push_back(".png");
    findAllFiles(Tiles, Formats);
    //added tiles
    for (uint i = 1; i <= height * width; i++)
    {
        TileMap.push_back(std::move(std::shared_ptr<PrimitiveQuad>(new PrimitiveQuad)));
    }

    //set position
    uint x = 0, y = 0;
    for (auto t : TileMap)
    {
        t->setPosition(x * size_x, y * size_y);

        x++;
        if (x == width)
        {
            y++;
            x = 0;
        }
    }

    //draw horizontal lines
    for(uint i = 1; i < y; i++)
    {
        sf::Vertex line[] =
                {
                    sf::Vertex({TileMap[i * width]->getPosition().x, TileMap[i * width]->getPosition().y}, sf::Color(42, 76, 61)),
                    sf::Vertex({TileMap[width-1]->getPosition().x + TILE_SIZE_DEFAULT, TileMap[i * width]->getPosition().y}, sf::Color(42, 76, 61))
                };
        LineGrid.push_back(std::pair<sf::Vertex, sf::Vertex>(line[0], line[1]));
    }
    //draw vertical lines
    for(uint i = 1; i < width; i++)
    {
        sf::Vertex line[] =
                {
                        sf::Vertex({TileMap[i]->getPosition().x, TileMap[i]->getPosition().y}, sf::Color(42, 76, 61)),
                        sf::Vertex({TileMap[i]->getPosition().x, TileMap[width * height - 1]->getPosition().y + TILE_SIZE_DEFAULT}, sf::Color(42, 76, 61))
                };
        LineGrid.push_back(std::pair<sf::Vertex, sf::Vertex>(line[0], line[1]));
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
                sf::Vector2f MouseGlobalPosition{window.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y})};
                bool clickCondition =
                        MouseGlobalPosition.x > t->getPosition().x && MouseGlobalPosition.y > t->getPosition().y
                        && MouseGlobalPosition.x < t->getPosition().x + t->getSize().x
                        && MouseGlobalPosition.y < t->getPosition().y + t->getSize().y;
                if (clickCondition)
                {
                    std::cout << "Current mode = " << CurrentMode << std::endl;
                    switch (CurrentMode)
                    {
                        case EditorMode::ADD:
                        {
                            int count = 0;
                            for (auto o : ObjList)
                            {
                                if (o->getPosition() == t->getPosition())
                                {
                                    count++;
                                }
                            }
                            ObjList.push_back(std::move(std::shared_ptr<TileEntity>(
                                    new TileEntity(std::string("Obj" + std::to_string(ObjList.size())), CurrentPathFile,
                                                   {t->getPosition().x, t->getPosition().y}, count))));

//                            ObjList.back()->setIndex(count);
                            ObjectListBox->addItem(ObjList.back()->Name);
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
                                                  << " object" << " (index: " << o->getIndex() << ") Name: " << o->Name
                                                  << std::endl;

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
            case sf::Keyboard::R:
            {
                drawTileMap(128, 128);
                for(auto t : TileMap)
                {
                    t->setSize({128, 128});
                }
                for(auto o : ObjList)
                {
                    o->setSize({128, 128});
                }
                break;
            }
        }
    }
}
void MapEditor::ChangeScrollablePanelStatus(bool val)
{
    canScroled = val;
}
void MapEditor::LoadFromFile(std::string fileName, std::vector<std::shared_ptr<TileEntity>> &obj)
{
    b_mutex.lock();
    mio.LoadFromFile(fileName, obj);
    b_mutex.unlock();
    ObjectListBox->removeAllItems();
    for(auto o : obj)
    {
        ObjectListBox->addItem(o->Name);
    }
}
void MapEditor::SaveToFile(std::string fileName, std::vector<std::shared_ptr<TileEntity>> obj)
{
    b_mutex.lock();
    mio.SaveToFile(fileName, obj);
    b_mutex.unlock();
}
