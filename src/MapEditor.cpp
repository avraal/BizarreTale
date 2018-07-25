// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// Created by andrew on 03.04.18.
//

#include <thread>
#include "MapEditor.h"
#include "CPrimitiveQuad.hpp"
#include "Entity/EObject.hpp"

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

    LoadUI();

    gui.add(infoPanel);
    gui.add(scrollPanel);
    gui.add(ObjectListBox);
    gui.add(scrollProperties);

    window.setKeyRepeatEnabled(true);
    window.setVerticalSyncEnabled(true);

    level = new Level(0, "Test");
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

        for (auto g : LineGrid)
        {
            sf::Vertex line[] =
                    {
                            g.first,
                            g.second
                    };
            window.draw(line, 2, sf::Lines);
        }
//        level->draw(window);
        for (auto d : dr1)
        {
            window.draw(*d);
        }
        infoObjCountLabel->setText("Object count: " + std::to_string(level->getObjCount()));
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
        FileFormats.emplace_back(".*");
    }
    if ((dir = opendir(MapEditor::ImageDirectory.c_str())) != nullptr)
    {
        while ((directory = readdir(dir)) != nullptr)
        {
            char *last = strrchr(directory->d_name, '.');
            if (last != nullptr)
            {
                for (const auto &f : FileFormats)
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
void MapEditor::SelectImage(const std::string &imagePath)
{
    CurrentPathFile = imagePath;
    CurrentMode = EditorMode::ADD;
    std::cout << "Prepare to add object" << std::endl;
}
void MapEditor::drawTileMap(float size_x, float size_y)
{
    LineGrid.clear();
    TileMap.clear();
    int height = 10;
    int width = 15;
    std::vector<std::string> Tiles;
    std::vector<std::string> Formats;
    Formats.emplace_back(".png");
    findAllFiles(Tiles, Formats);
    //added tiles
    for (uint i = 1; i <= height * width; i++)
    {
        TileMap.push_back(new CPrimitiveQuad());
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
    for (uint i = 1; i < y; i++)
    {
        sf::Vertex line[] =
                {
                        sf::Vertex({TileMap[i * width]->getPosition().x, TileMap[i * width]->getPosition().y},
                                   sf::Color(42, 76, 61)),
                        sf::Vertex({TileMap[width - 1]->getPosition().x + TILE_SIZE_DEFAULT,
                                    TileMap[i * width]->getPosition().y}, sf::Color(42, 76, 61))
                };
        LineGrid.emplace_back(std::pair<sf::Vertex, sf::Vertex>(line[0], line[1]));
    }
    //draw vertical lines
    for (uint i = 1; i < width; i++)
    {
        sf::Vertex line[] =
                {
                        sf::Vertex({TileMap[i]->getPosition().x, TileMap[i]->getPosition().y}, sf::Color(42, 76, 61)),
                        sf::Vertex({TileMap[i]->getPosition().x,
                                    TileMap[width * height - 1]->getPosition().y + TILE_SIZE_DEFAULT},
                                   sf::Color(42, 76, 61))
                };
        LineGrid.emplace_back(std::pair<sf::Vertex, sf::Vertex>(line[0], line[1]));
    }

}
void MapEditor::MouseCallbacks(sf::Event event)
{
    if (event.type == sf::Event::MouseButtonPressed)
    {
        if (event.mouseButton.button == sf::Mouse::Left &&
            !scrollPanel->mouseOnWidget(tgui::Vector2f(event.mouseButton.x, event.mouseButton.y)) &&
            !scrollProperties->mouseOnWidget(tgui::Vector2f(event.mouseButton.x, event.mouseButton.y)) &&
            !ObjectListBox->mouseOnWidget(tgui::Vector2f(event.mouseButton.x, event.mouseButton.y)))
        {
            sf::Vector2f MouseGlobalPosition{window.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y})};
            bool clickCondition;

            switch (CurrentMode)
            {
                case EditorMode::ADD:
                {
                    for (auto t : TileMap)
                    {
                        clickCondition =
                                MouseGlobalPosition.x > t->getPosition().x &&
                                MouseGlobalPosition.y > t->getPosition().y &&
                                MouseGlobalPosition.x < t->getPosition().x + t->getTextureSize().x &&
                                MouseGlobalPosition.y < t->getPosition().y + t->getTextureSize().y;
                        if (clickCondition)
                        {
                            auto eobj = new EObject(CurrentPathFile);
                            level->addObject(eobj);
                            eobj->setPosition(t->getPosition());
                            if (level->getObjCount() > 1)
                            {
                                int count = 0;
                                for (auto o : level->getAllObjects())
                                {
                                    if (o == eobj)
                                        continue;
                                    if (o->getBody() != nullptr && eobj->getBody() != nullptr)
                                    {
                                        if (o->getPosition() == eobj->getPosition())
                                        {
                                            count++;
                                        }
                                    }
                                }
                                eobj->getBody()->setIndex(count);
                            }
                            for (auto o : eobj->getDrawable())
                            {
                                dr1.push_back(o);
                            }
                            const std::string objName = level->getObject(level->getObjCount() - 1)->getName();
                            ObjectListBox->addItem(objName);
                            ObjectListBox->setSelectedItem(objName);
                        }
                    }
                    break;
                }
                case EditorMode::SELECT:
                {
                    for (auto o : level->getAllObjects())
                    {
                        clickCondition =
                                MouseGlobalPosition.x > o->getBody()->getPosition().x &&
                                MouseGlobalPosition.y > o->getBody()->getPosition().y &&
                                MouseGlobalPosition.x <
                                o->getBody()->getPosition().x + o->getBody()->getTextureSize().x &&
                                MouseGlobalPosition.y <
                                o->getBody()->getPosition().y + o->getBody()->getTextureSize().y;
                        if (clickCondition)
                        {
                            SelectedEntities.clear();
                            std::cout << "Edit x: " << o->getBody()->getPosition().x << " y: "
                                      << o->getBody()->getPosition().y
                                      << " object " << o->getName() << " (index: " << o->getBody()->getIndex() << ")"
                                      << std::endl;
                            std::cout << "-----------" << std::endl;
                            ObjectListBox->setSelectedItem(o->getName());
                        }
                    }
                    break;
                }
                case EditorMode::MULTISELECT:
                {
                    for (auto o : level->getAllObjects())
                    {
                        clickCondition =
                                MouseGlobalPosition.x > o->getBody()->getPosition().x &&
                                MouseGlobalPosition.y > o->getBody()->getPosition().y &&
                                MouseGlobalPosition.x <
                                o->getBody()->getPosition().x + o->getBody()->getTextureSize().x &&
                                MouseGlobalPosition.y <
                                o->getBody()->getPosition().y + o->getBody()->getTextureSize().y;
                        if (clickCondition)
                        {
//                            if (SelectedEntities.empty())
//                            {
//                                SelectedEntities.insert({SelectedEntity});
//                            }
                            SelectedEntities.insert({dynamic_cast<EObject*>(o)});
                            ObjectListBox->setSelectedItem(o->getName());
                            for (auto s : SelectedEntities)
                            {
                                std::cout << s->getName() << std::endl;
                            }
                        }
                    }
                    break;
                }
            }
        }
        if (event.mouseButton.button == sf::Mouse::Right)
        {
            sf::Vector2i Mouse = sf::Mouse::getPosition(window);
            float w = window.mapPixelToCoords(Mouse).x;
            float h = window.mapPixelToCoords(Mouse).y;
            MainCamera.setCenter(w, h);
        }
    }

    if (event.type == sf::Event::MouseWheelScrolled)
    {
        if (canScroled)
        {
            ZoomViewAt({event.mouseWheelScroll.x, event.mouseWheelScroll.y},
                       event.mouseWheelScroll.delta > 0 ? (1.0f / 1.1f) : 1.1f);
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
    if (event.type == sf::Event::KeyReleased)
    {
        switch (event.key.code)
        {
            case sf::Keyboard::LShift:
            {
                CurrentMode = EditorMode::SELECT;
                std::cout << "Edit mode enabled" << std::endl;
                break;
            }
        }
    }
    if (event.type == sf::Event::KeyPressed)
    {
        switch (event.key.code)
        {
            case sf::Keyboard::E:
            {
                CurrentMode = EditorMode::SELECT;
                std::cout << "Edit mode enabled" << std::endl;
                break;
            }
            case sf::Keyboard::A:
            {
                CurrentMode = EditorMode::ADD;
                if(SelectedEntity != nullptr)
                {
                    if (SelectedEntity->getBody() != nullptr)
                    {
                        SelectedEntity->getBody()->hideBounds();
                    }
                }
                SelectedEntity = nullptr;
                for(auto o : level->getAllObjects())
                {
                    if(o->getBody() != nullptr)
                    {
                        o->getBody()->hideBounds();
                    }
                }
                SelectedEntities.clear();
                ObjectListBox->deselectItem();
                std::cout << "Prepare to add new object" << std::endl;
                break;
            }
            case sf::Keyboard::Escape:
            {
                window.close();
                break;
            }
            case sf::Keyboard::LShift:
            {
                CurrentMode = EditorMode::MULTISELECT;
                std::cout << "Prepare to selected one more object" << std::endl;
                break;
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
                //            case sf::Keyboard::Space:
                //            {
                //                std::thread thr(&MapEditor::SaveToFile, this, "test.mio", ObjList);
                //                thr.join();
                //                break;
                //            }
                //            case sf::Keyboard::LControl:
                //            {
                //                std::thread thr(&MapEditor::LoadFromFile, this, "test.mio", std::ref(ObjList));
                //                thr.join();
                //                break;
                //            }
            case sf::Keyboard::R:
            {
                drawTileMap(128, 128);
                for (auto t : TileMap)
                {
                    t->setSize({128, 128});
                }
                for (auto o : level->getAllObjects())
                {
                    //                    o->setSize({128, 128});
                    o->getBody()->setSize({128, 128});
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
void MapEditor::LoadFromFile(std::string fileName, std::vector<std::shared_ptr<CTile>> &obj)
{
    b_mutex.lock();
    mio.LoadFromFile(fileName, obj);
    b_mutex.unlock();
    ObjectListBox->removeAllItems();
    for (auto o : obj)
    {
        //        ObjectListBox->addItem(o->GetName());
    }
}
void MapEditor::SaveToFile(std::string fileName, std::vector<std::shared_ptr<CTile>> obj)
{
    b_mutex.lock();
    mio.SaveToFile(fileName, obj);
    b_mutex.unlock();
}
void MapEditor::addInfoToPropertiesPanel()
{
    if (ObjectListBox->getSelectedItemIndex() < 0)
    {
        return;
    }
    SelectedEntity = findEntityByName(ObjectListBox->getSelectedItem().toAnsiString());
    if (SelectedEntity == nullptr)
    {
        std::cerr << "addInfoToPropertiesPanel returned null reference" << std::endl;
        return;
    }
    objPropChangeNameBox->setText(SelectedEntity->getName());
    objPositionX->setText(std::to_string(SelectedEntity->getPosition().x));
    objPositionY->setText(std::to_string(SelectedEntity->getPosition().y));
    for (auto o : level->getAllObjects())
    {
        if (o != SelectedEntity)
        {
            if (o->getBody() != nullptr)
            {
                o->getBody()->hideBounds();
            }
        }
    }
    if (!SelectedEntities.empty())
    {
        for (auto s : SelectedEntities)
        {
            if (s->getBody() != nullptr)
            {
                s->getBody()->drawBounds();
                s->getBody()->ShowBounds = true;
            }
        }
    } else
    {
        auto body = SelectedEntity->getBody();
        if (!body)
        {
            std::cerr << "getBody: body returned nullptr" << std::endl;
            objIndexEditBox->setText("0");
            return;
        }

        body->drawBounds();
        body->ShowBounds = true;
        objIndexEditBox->setText(std::to_string(body->getIndex()));
    }
}
EObject *MapEditor::findEntityByName(const std::string &ObjName)
{
    for (auto &o : level->getAllObjects())
    {
        if (o->getName() == ObjName)
        {
            //TODO: remove cast
            return dynamic_cast<EObject*>(o);
        }
    }
    std::cerr << "findEntityByName returned null reference" << std::endl;
    return nullptr;
}
void MapEditor::UpdateObjectFromProperties()
{
    if (SelectedEntity == nullptr)
    {
        return;
    }
    if (!SelectedEntities.empty())
    {
        for (auto s : SelectedEntities)
        {
            s->setPosition(std::atof(objPositionX->getText().toAnsiString().c_str()),
                           std::atof(objPositionY->getText().toAnsiString().c_str()));
            if (s->getBody() != nullptr)
            {
                s->getBody()->setIndex(std::stoi(objIndexEditBox->getText().toAnsiString()));
            }
            s->setName(objPropChangeNameBox->getText().toAnsiString());
        }
    } else
    {
        auto body = SelectedEntity->getBody();
        if (!body)
        {
            std::cerr << "getBody: body returned nullptr" << std::endl;
            return;
        }
        SelectedEntity->setPosition(std::atof(objPositionX->getText().toAnsiString().c_str()),
                                    std::atof(objPositionY->getText().toAnsiString().c_str()));
        body->setIndex(std::stoi(objIndexEditBox->getText().toAnsiString()));
        SelectedEntity->setName(objPropChangeNameBox->getText().toAnsiString());
    }

    int count = 0;
    for (auto o : level->getAllObjects())
    {
        if (o == SelectedEntity)
        {
            continue;
        }
        if (o->getName() == SelectedEntity->getName())
        {
            o->setName(SelectedEntity->getName() + '(' + std::to_string(++count) + ')');
        }
        if (o->getPosition() == SelectedEntity->getPosition())
        {
            if (o->getBody()->getIndex() == SelectedEntity->getBody()->getIndex())
            {
                SelectedEntity->getBody()->setIndex(SelectedEntity->getBody()->getIndex() + 1);
            }
        }
    }

    sortObjects();
}

void MapEditor::sortObjects()
{
    ObjectListBox->removeAllItems();

    for(auto o : level->getAllObjects())
    {
        ObjectListBox->addItem(o->getName());
    }

    std::sort(level->getAllObjects().begin(), level->getAllObjects().end(),
              [](IEntity *t1, IEntity *t2)
              {
                  if (t1->getBody() != nullptr && t2->getBody() != nullptr)
                  {
                      return t1->getBody()->getIndex() < t2->getBody()->getIndex();
                  }
                  return false;
              });

    dr1.clear();

    for (auto o : level->getAllObjects())
    {
        for (auto &d : o->getDrawable())
        {
            dr1.push_back(d);
        }
    }
}

void MapEditor::LoadUI()
{
    ObjectListBox = ::tgui::ListBox::create();
    scrollPanel = tgui::ScrollablePanel::create({"100%", "25%"});
    objectProperties = tgui::Panel::create();

    scrollPanel->setPosition(0, window.getSize().y - 200);
    scrollPanel->setSize(window.getSize().x, 200);

    ObjectListBox->setPosition(0, 0);
    ObjectListBox->setSize(250, window.getSize().y - scrollPanel->getSize().y);
    ObjectListBox->setItemHeight(25);
    ObjectListBox->getRenderer()->setBackgroundColor(sf::Color(16, 16, 16, 200));
    ObjectListBox->getRenderer()->setTextColor(sf::Color::White);
    ObjectListBox->connect(ObjectListBox->onItemSelect.getName(), &MapEditor::addInfoToPropertiesPanel, this);

    //------------------------------------------------------------------------------------------------------------------
    scrollProperties = tgui::ScrollablePanel::create();
    scrollProperties->setPosition(window.getSize().x - 250, 0);
    scrollProperties->setSize(250, window.getSize().y - scrollPanel->getSize().y);
    scrollProperties->getRenderer()->setBackgroundColor(sf::Color(16, 16, 16, 200));

    scrollProperties->add(objectProperties);

    objectProperties->setPosition(0, 0);
    //    objectProperties->setSize(250, window.getSize().y - scrollPanel->getSize().y);
    //    objectProperties->setSize(scrollProperties->getSize());
    objectProperties->getRenderer()->setBackgroundColor(sf::Color(16, 16, 16, 200));
    objectProperties->getRenderer()->setPadding({5, 5});

    objPropName = tgui::Label::create();
    objPropName->getRenderer()->setTextColor(sf::Color::White);
    objPropName->setTextSize(INFO_PANEL_TEXT_SIZE);
    objPropName->setText("Object:");
    objPropName->setPosition(0, 4);

    objPropChangeNameBox = tgui::EditBox::create();
    objPropChangeNameBox->setPosition(objPropName->getSize().x + 4, 0);
    objPropChangeNameBox->setSize(objectProperties->getSize().x / 2, INFO_PANEL_TEXT_SIZE + 10);
    objPropChangeNameBox->setTextSize(objPropName->getTextSize());
    objPropChangeNameBox->getRenderer()->setTextColor(sf::Color(210, 210, 210));
    objPropChangeNameBox->getRenderer()->setBackgroundColor(sf::Color(0, 0, 0, 200));
    objPropChangeNameBox->getRenderer()->setBackgroundColorDisabled(sf::Color(0, 0, 0, 225));
    objPropChangeNameBox->getRenderer()->setBackgroundColorFocused(sf::Color(0, 0, 0, 200));
    objPropChangeNameBox->getRenderer()->setBackgroundColorHover(sf::Color(0, 0, 0, 200));
    objPropChangeNameBox->getRenderer()->setBorderColor(sf::Color(0, 0, 0, 0));
    objPropChangeNameBox->getRenderer()->setBorderColorDisabled(sf::Color(0, 0, 0, 0));
    objPropChangeNameBox->getRenderer()->setBorderColorFocused(sf::Color(0, 0, 0, 0));
    objPropChangeNameBox->getRenderer()->setBorderColorHover(sf::Color(0, 0, 0, 0));
    objPropChangeNameBox->connect(objPropChangeNameBox->onReturnKeyPress.getName(),
                                  &MapEditor::UpdateObjectFromProperties, this);

    objPositionLabel = tgui::Label::create();
    objPositionLabel->getRenderer()->setTextColor(sf::Color::White);
    objPositionLabel->setTextSize(INFO_PANEL_TEXT_SIZE);
    objPositionLabel->setText("Position");
    objPositionLabel->setPosition(0, objPropName->getPosition().y + objPropName->getSize().y + 4);

    objPositionLabelX = tgui::Label::copy(objPositionLabel);
    objPositionLabelX->setText("x:");
    objPositionLabelX->setPosition(0, objPositionLabel->getPosition().y + objPositionLabel->getSize().y + 4);

    objPositionX = tgui::EditBox::copy(objPropChangeNameBox);
    objPositionX->setPosition(objPositionLabelX->getSize().x + 4, objPositionLabelX->getPosition().y);

    objPositionLabelY = tgui::Label::copy(objPositionLabel);
    objPositionLabelY->setText("y:");
    objPositionLabelY->setPosition(0, objPositionLabelX->getPosition().y + objPositionLabelX->getSize().y + 4);

    objPositionY = tgui::EditBox::copy(objPropChangeNameBox);
    objPositionY->setPosition(objPositionLabelY->getSize().x + 4, objPositionLabelY->getPosition().y);

    objIndexLabel = tgui::Label::copy(objPositionLabel);
    objIndexLabel->setText("Index:");
    objIndexLabel->setPosition(0, objPositionLabelY->getPosition().y + objPositionLabelY->getSize().y + 4);

    objIndexEditBox = tgui::EditBox::copy(objPositionY);
    objIndexEditBox->setPosition(objIndexLabel->getSize().x + 4, objIndexLabel->getPosition().y);

    objectProperties->add(objPropName);
    objectProperties->add(objPropChangeNameBox);
    objectProperties->add(objPositionLabel);
    objectProperties->add(objPositionLabelX);
    objectProperties->add(objPositionLabelY);
    objectProperties->add(objPositionX);
    objectProperties->add(objPositionY);
    objectProperties->add(objIndexLabel);
    objectProperties->add(objIndexEditBox);

    objConfirmChanges = tgui::Button::create();
    scrollProperties->add(objConfirmChanges);
    objConfirmChanges->setPosition(4, scrollProperties->getSize().y - objConfirmChanges->getSize().y - 4);
    objConfirmChanges->setText("Confirm");
    objConfirmChanges->connect(objConfirmChanges->onClick.getName(), &MapEditor::UpdateObjectFromProperties, this);
    //------------------------------------------------------------------------------------------------------------------
    auto grid = tgui::Grid::create();

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

    infoPanel = tgui::Panel::create({200, 100});
    infoPanel->setPosition(scrollProperties->getPosition().x - infoPanel->getSize().x, 0);
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

    scrollPanel->connect(scrollPanel->onMouseLeave.getName(), &MapEditor::ChangeScrollablePanelStatus, this, true);
    scrollPanel->connect(scrollPanel->onMouseEnter.getName(), &MapEditor::ChangeScrollablePanelStatus, this, false);

    scrollProperties->connect(scrollProperties->onMouseLeave.getName(), &MapEditor::ChangeScrollablePanelStatus, this,
                              true);
    scrollProperties->connect(scrollProperties->onMouseEnter.getName(), &MapEditor::ChangeScrollablePanelStatus, this,
                              false);

    ObjectListBox->connect(ObjectListBox->onMouseLeave.getName(), &MapEditor::ChangeScrollablePanelStatus, this, true);
    ObjectListBox->connect(ObjectListBox->onMouseEnter.getName(), &MapEditor::ChangeScrollablePanelStatus, this, false);
}

