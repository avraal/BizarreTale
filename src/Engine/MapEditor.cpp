#include <utility>

// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// Created by andrew on 03.04.18.
//

#include <thread>
#include "MapEditor.h"
#include "Components/CPrimitiveQuad.hpp"
#include "Entity/EObject.hpp"
#include "Util/IDGenerator.hpp"

MapEditor::MapEditor(const std::string &Name) : Level(Name)
{
    ImageDirectory = "";
    CurrentPathFile = "";
    ImagesFormats.push_back(".png");
    ImagesFormats.push_back(".jpg");
    CameraSpeed = 4.0f;
    showInfo = true;
    canScroll = true;
    CurrentMode = EditorMode::SELECT;
    SelectedEntity = nullptr;
    backGroundColor = sf::Color(42, 76, 61);
}

bool MapEditor::prepareLevel(sf::RenderWindow &window)
{
    if (!findAllFiles(PathToImages, ImagesFormats))
    {
        return false;
    }
    Level::prepareLevel(window);
    drawTileMap(TILE_SIZE_DEFAULT, TILE_SIZE_DEFAULT);

    UserInterface->gui->add(infoPanel);
    UserInterface->gui->add(scrollPanel);
    UserInterface->gui->add(ObjectListBox);
    UserInterface->gui->add(scrollProperties);

    tgui::Theme theme{"tgui_themes/Black.txt"};
    return true;
}

void MapEditor::draw(sf::RenderWindow &window)
{
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
    Level::draw(window);
    infoObjCountLabel->setText("Object count: " + std::to_string(objDetails->objCount));
    infoFPSLabel->setText("FPS: " + std::to_string((us_int) fps));
    objDetails->objReferenceCount = 0;
    objDetails->drawableReferenceCount = 0;
    for (const auto &item : ObjList)
    {
        objDetails->objReferenceCount += item.use_count();
    }
    for (const auto &component : DrawableComponents)
    {
        objDetails->drawableReferenceCount += component.use_count();
    }
    infoObjReferenceCount->setText("ObjReferenceCount: " + std::to_string(objDetails->objReferenceCount));
    infoDrawableObjCountLabel->setText("Drawable count: " + std::to_string(objDetails->drawableCount));
    infoDrawableReferenceCount->setText("DrawableReferenceCount: " + std::to_string(objDetails->drawableReferenceCount));
}

bool MapEditor::findAllFiles(std::vector<std::string> &Container, std::vector<std::string> FileFormats)
{
    bool result = false;
    DIR *dir;
    dirent *directory;
    if (FileFormats.empty())
    {
        FileFormats.emplace_back(".*");
    }
    if ((dir = opendir(ImageDirectory.c_str())) != nullptr)
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
                        Container.push_back(ImageDirectory + directory->d_name);
                        result = true;
                    }
                }
            }
        }
        closedir(dir);
    } else
    {
        std::cerr << "Can't open a dir" << std::endl;
        result = false;
    }
    return result;
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
    us_int height = 10;
    us_int width = 15;
    std::vector<std::string> Tiles;
    std::vector<std::string> Formats;
    Formats.emplace_back(".png");
    findAllFiles(Tiles, Formats);
    //added tiles
    for (us_int i = 1; i <= height * width; i++)
    {
        TileMap.push_back(new CPrimitiveQuad());
    }

    //set position
    us_int x = 0, y = 0;
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
    for (us_int i = 1; i < y; i++)
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
    for (us_int i = 1; i < width; i++)
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
void MapEditor::MouseCallbacks(sf::RenderWindow &window, sf::Event &event)
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
                            auto eobj = std::make_shared<EObject>();
                            auto body = std::make_shared<CTile>(IDGenerator::getNextId(), "body", CurrentPathFile,
                                                                eobj->getPosition());
                            eobj->setPosition(t->getPosition());
                            body->Attach(eobj);
                            addObject(eobj);
                            const std::string objName = ObjList.back()->getName();
                            ObjectListBox->addItem(objName);
                            ObjectListBox->setSelectedItem(objName);
                        }
                    }
                    break;
                }
                case EditorMode::SELECT:
                {
                    for (auto o : ObjList)
                    {
                        auto body = o->getComponent<CPrimitiveQuad>("body");
                        clickCondition =
                                MouseGlobalPosition.x > body->getPosition().x &&
                                MouseGlobalPosition.y > body->getPosition().y &&
                                MouseGlobalPosition.x < body->getPosition().x + body->getTextureSize().x &&
                                MouseGlobalPosition.y < body->getPosition().y + body->getTextureSize().y;

                        if (clickCondition)
                        {
                            SelectedEntities.clear();
                            std::cout << "Edit x: " << body->getPosition().x << " y: "
                                      << body->getPosition().y
                                      << " object " << o->getName() << " (index: " << body->getIndex() << ")"
                                      << std::endl;
                            std::cout << "-----------" << std::endl;
                            ObjectListBox->setSelectedItem(o->getName());
                            ///this handler exec in addInfoToPropertiesPanel
                        }
                    }
                    break;
                }
                case EditorMode::MULTISELECT:
                {
                    for (auto o : ObjList)
                    {
                        auto body = o->getComponent<CPrimitiveQuad>("body");
                        clickCondition =
                                MouseGlobalPosition.x > body->getPosition().x &&
                                MouseGlobalPosition.y > body->getPosition().y &&
                                MouseGlobalPosition.x < body->getPosition().x + body->getTextureSize().x &&
                                MouseGlobalPosition.y < body->getPosition().y + body->getTextureSize().y;
                        if (clickCondition)
                        {
                            SelectedEntities.insert(std::pair<us_int, std::shared_ptr<IEntity>>(o->GetId(), o));
                            ObjectListBox->setSelectedItem(o->getName());
                            for (auto s : SelectedEntities)
                            {
                                std::cout << s.second->getName() << std::endl;
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
            MainCamera->setCenter(w, h);
        }
    }

    if (event.type == sf::Event::MouseWheelScrolled)
    {
        if (canScroll)
        {
            ZoomViewAt(window, {event.mouseWheelScroll.x, event.mouseWheelScroll.y},
                       event.mouseWheelScroll.delta > 0 ? (1.0f / 1.1f) : 1.1f);
        }
    }
}

void MapEditor::ZoomViewAt(sf::RenderWindow &window, sf::Vector2i pixel, float zoom)
{
    const sf::Vector2f beforeCoord{window.mapPixelToCoords(pixel)};
    MainCamera->zoom(zoom);
    const sf::Vector2f afterCoord{window.mapPixelToCoords(pixel)};
    const sf::Vector2f offsetCoord{beforeCoord - afterCoord};
    MainCamera->move(offsetCoord);
}
void MapEditor::KeyBoardCallbacks(sf::RenderWindow &window, sf::Event &event)
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
            case sf::Keyboard::Delete:
            {
                if (ObjList.size() > 0 && SelectedEntity)
                {
                    for (auto it = SelectedEntities.begin(); it != SelectedEntities.end();)
                    {
                        std::string _n = it->second->getName();
                        if (DestroyEntity(it->first))
                        {
                            ObjectListBox->removeItem(_n);
                            it = SelectedEntities.erase(it);
                        } else
                        {
                            ++it;
                        }
                    }
                    ObjectListBox->removeItem(SelectedEntity->getName());
                    if (DestroyEntity(SelectedEntity->GetId()))
                    {
                        ClearObjectProperties();
                    }
                }
                break;
            }
            case sf::Keyboard::E:
            {
                CurrentMode = EditorMode::SELECT;
                std::cout << "Edit mode enabled" << std::endl;
                break;
            }
            case sf::Keyboard::A:
            {
                CurrentMode = EditorMode::ADD;
                if (SelectedEntity != nullptr)
                {
                    if (auto body = SelectedEntity->getComponent<CPrimitiveQuad>("body"); body)
                    {
                        body->hideBounds();
                    }
                }
                SelectedEntity = nullptr;
                for (auto o : ObjList)
                {
                    if (auto body = o->getComponent<CPrimitiveQuad>("body"); body)
                    {
                        body->hideBounds();
                    }
                }
                SelectedEntities.clear();
                ObjectListBox->deselectItem();
                ClearObjectProperties();
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
                MainCamera->move(CameraSpeed, 0.0f);
                break;
            }
            case sf::Keyboard::Left:
            {
                MainCamera->move(-CameraSpeed, 0.0f);
                break;
            }
            case sf::Keyboard::Up:
            {
                MainCamera->move(0.0f, -CameraSpeed);
                break;
            }
            case sf::Keyboard::Down:
            {
                MainCamera->move(0.0f, CameraSpeed);
                break;
            }
            case sf::Keyboard::F3:
            {
                showInfo = !showInfo;
                infoPanel->setVisible(showInfo);
                break;
            }
            case sf::Keyboard::R:
            {
                drawTileMap(128, 128);
                for (auto t : TileMap)
                {
                    t->setSize({128, 128});
                }
                for (auto o : ObjList)
                {
                    o->getComponent<CPrimitiveQuad>("body")->setSize({128, 128});
                }
                break;
            }
        }
    }
}

void MapEditor::addInfoToPropertiesPanel()
{
    if (ObjectListBox->getSelectedItemIndex() < 0)
    {
        return;
    }
    SelectedEntity = getObjectByName(ObjectListBox->getSelectedItem().toAnsiString());
    if (SelectedEntity == nullptr)
    {
        std::cerr << "addInfoToPropertiesPanel returned null reference" << std::endl;
        return;
    }
    ClearObjectProperties();
    objPropChangeNameBox->setText(SelectedEntity->getName());
    objPositionX->setText(std::to_string(SelectedEntity->getPosition().x));
    objPositionY->setText(std::to_string(SelectedEntity->getPosition().y));
    for (auto o : ObjList)
    {
        if (o != SelectedEntity)
        {
            if (auto body = o->getComponent<CPrimitiveQuad>("body"); body)
            {
                body->hideBounds();
            }
        }
    }
    if (!SelectedEntities.empty())
    {
        for (auto s : SelectedEntities)
        {
            if (auto body = s.second->getComponent<CPrimitiveQuad>("body"); body)
            {
                body->drawBounds();
                body->ShowBounds = true;
            }
        }
    } else
    {
        if (auto body = SelectedEntity->getComponent<CPrimitiveQuad>("body"); !body)
        {
            std::cerr << "getBody: body returned nullptr" << std::endl;
            objIndexEdit->label->setText("0");
            return;
        }
        auto body = SelectedEntity->getComponent<CPrimitiveQuad>("body");

        body->drawBounds();
        body->ShowBounds = true;
        objIndexEdit->setText(std::to_string(body->getIndex()));
        tgui::Picture::Ptr compPic;
        tgui::Button::Ptr addComp;
        tgui::ScrollablePanel::Ptr compList;

        compPic = tgui::Picture::create(body->getTexturePath());
        addComp = tgui::Button::create("Add component");
        compList = tgui::ScrollablePanel::create({objectProperties->getSize().x, 250});

        compPic->setPosition(objIndexEdit->getPosition().x,
                             objIndexEdit->getPosition().y + objIndexEdit->getSize().y + 4);
        addComp->setPosition(compPic->getPosition().x, compPic->getPosition().y + compPic->getSize().y + 4);
        addComp->setSize(objectProperties->getSize().x - 4, addComp->getSize().y);
        addComp->connect(addComp->onClick.getName(), [this]()
        {
            std::string pathToImage = "";
            nfdchar_t *outPath = nullptr;
            nfdresult_t result = NFD_OpenDialog(nullptr, nullptr, &outPath);
            if (result == NFD_OKAY)
            {
                auto comp = std::make_shared<CTile>(IDGenerator::getNextId(), "comp1", outPath,
                                                    SelectedEntity->getPosition());
                comp->Attach(SelectedEntity);
                delete outPath;
                addInfoToPropertiesPanel();
            }

        });

        compList->setPosition(objIndexEdit->getPosition().x, addComp->getPosition().y + addComp->getSize().y + 4);
        compList->getRenderer()->setBackgroundColor(sf::Color(0, 0, 0, 140));

        objectProperties->add(compPic, "compPic");
        objectProperties->add(compList, "compList");
        objectProperties->add(addComp, "addComp");

        us_int posY = 0;
        for (const auto &item : SelectedEntity->getDrawable())
        {
            if (item != body)
            {
                tgui::Picture::Ptr c = tgui::Picture::create(item->getTexturePath());
                c->setPosition(0, posY);
                compList->add(c);
                posY += c->getSize().y + 4;
            }
        }
    }
}

void MapEditor::ClearObjectProperties()
{
    objPropChangeNameBox->setText("");
    objIndexEdit->setText("");
    objPositionX->setText("");
    objPositionY->setText("");

    objectProperties->remove(objectProperties->get("compPic"));
    objectProperties->remove(objectProperties->get("compList"));
    objectProperties->remove(objectProperties->get("addComp"));
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
            s.second->setPosition(std::atof(objPositionX->getText().toAnsiString().c_str()),
                                  std::atof(objPositionY->getText().toAnsiString().c_str()));
            if (auto body = s.second->getComponent<CPrimitiveQuad>("body"); body)
            {
                body->setIndex(std::stoi(objIndexEdit->getText().toAnsiString()));
            }
        }
    } else
    {
        if (auto body = SelectedEntity->getComponent<CPrimitiveQuad>("body"); !body)
        {
            std::cerr << "getBody: body returned nullptr" << std::endl;
            return;
        }
        auto body = SelectedEntity->getComponent<CPrimitiveQuad>("body");
        SelectedEntity->setPosition(static_cast<float>(std::atof(objPositionX->getText().toAnsiString().c_str())),
                                    static_cast<float>(std::atof(objPositionY->getText().toAnsiString().c_str())));
        body->setIndex(std::stoi(objIndexEdit->getText().toAnsiString()));
        std::string beforeName = SelectedEntity->getName();
        SelectedEntity->setName(objPropChangeNameBox->getText().toAnsiString());
        ObjectListBox->changeItem(beforeName, SelectedEntity->getName());
    }

    us_int count = 0;
    for (auto o : ObjList)
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
            if (auto body = o->getComponent<CPrimitiveQuad>("body"); body)
            {
                if (body->getIndex() == SelectedEntity->getComponent<CPrimitiveQuad>("body")->getIndex())
                {
                    SelectedEntity->getComponent<CPrimitiveQuad>("body")->setIndex(
                            SelectedEntity->getComponent<CPrimitiveQuad>("body")->getIndex() + 1);
                }
            }
        }
    }

    for (const auto &o : ObjList)
    {
        std::cout << o->getName() << std::endl;
    }

    sortedObjectsByIndex();
}
void MapEditor::loadGui(sf::RenderWindow &window)
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

    objPropChangeNameBox = tgui::EditboxAndLabel::create("Object:");
    objPropChangeNameBox->label->getRenderer()->setTextColor(sf::Color::White);
    objPropChangeNameBox->label->setTextSize(INFO_PANEL_TEXT_SIZE);
    objPropChangeNameBox->setPosition({0, 4});
    objPropChangeNameBox->setSize(objectProperties->getSize().x / 2, INFO_PANEL_TEXT_SIZE + 10);
    objPropChangeNameBox->setTextSize(INFO_PANEL_TEXT_SIZE);
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
    objPositionLabel->setPosition(0, objPropChangeNameBox->getPosition().y + objPropChangeNameBox->getSize().y + 4);

    objPositionX = tgui::EditboxAndLabel::create("");
    objPositionX->label = tgui::Label::copy(objPositionLabel);
    objPositionX->label->setText("x:");
    objPositionX->setPosition({0, objPositionLabel->getPosition().y + objPositionLabel->getSize().y + 4});
    objPositionX->setRenderer(objPropChangeNameBox->getRenderer()->clone());

    objPositionY = tgui::EditboxAndLabel::create("");
    objPositionY->label = tgui::Label::copy(objPositionLabel);
    objPositionY->label->setText("y:");
    objPositionY->setPosition({0, objPositionX->getPosition().y + objPositionX->getSize().y + 4});
    objPositionY->setRenderer(objPropChangeNameBox->getRenderer()->clone());

    objIndexEdit = tgui::EditboxAndLabel::create("Index:");
    objIndexEdit->label = tgui::Label::copy(objPositionLabel);
    objIndexEdit->label->setText("Index:");
    objIndexEdit->setRenderer(objPositionY->getRenderer()->clone());
    objIndexEdit->setPosition({0, objPositionY->getPosition().y + objPositionY->getSize().y + 4});

    objectProperties->add(objPropChangeNameBox);
    objectProperties->add(objPositionLabel);
    objectProperties->add(objPositionX);
    objectProperties->add(objPositionY);
    objectProperties->add(objIndexEdit);

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
    us_int x = 0, y = 0;
    for (const auto &i : PathToImages)
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

    infoFPSLabel = tgui::Label::create();
    infoFPSLabel->getRenderer()->setTextColor(sf::Color::White);
    infoFPSLabel->setTextSize(INFO_PANEL_TEXT_SIZE);
    //    infoFPSLabel->setPosition(0, INFO_PANEL_TEXT_SIZE + 2);

    infoObjCountLabel = tgui::Label::create();
    infoObjCountLabel->getRenderer()->setTextColor(sf::Color::White);
    infoObjCountLabel->setTextSize(INFO_PANEL_TEXT_SIZE);
    infoObjCountLabel->setPosition(0, INFO_PANEL_TEXT_SIZE + 2);

    infoObjReferenceCount = tgui::Label::create();
    infoObjReferenceCount->getRenderer()->setTextColor(sf::Color::White);
    infoObjReferenceCount->setTextSize(INFO_PANEL_TEXT_SIZE);
    infoObjReferenceCount->setPosition(0, infoObjCountLabel->getPosition().y + INFO_PANEL_TEXT_SIZE + 2);

    infoDrawableObjCountLabel = tgui::Label::copy(infoObjReferenceCount);
    infoDrawableObjCountLabel->setPosition(0, infoObjReferenceCount->getPosition().y + INFO_PANEL_TEXT_SIZE + 2);

    infoDrawableReferenceCount = tgui::Label::copy(infoDrawableObjCountLabel);
    infoDrawableReferenceCount->setPosition(0, infoDrawableObjCountLabel->getPosition().y + INFO_PANEL_TEXT_SIZE + 2);

    infoPanel->add(infoObjCountLabel);
    infoPanel->add(infoFPSLabel);
    infoPanel->add(infoObjReferenceCount);
    infoPanel->add(infoDrawableObjCountLabel);
    infoPanel->add(infoDrawableReferenceCount);

    scrollPanel->connect(scrollPanel->onMouseLeave.getName(), [this]()
    {
        canScroll = true;
    });
    scrollPanel->connect(scrollPanel->onMouseEnter.getName(), [this]()
    {
        canScroll = false;
    });

    scrollProperties->connect(scrollProperties->onMouseLeave.getName(), [this]()
    {
        canScroll = true;
    });
    scrollProperties->connect(scrollProperties->onMouseEnter.getName(), [this]()
    {
        canScroll = false;
    });

    ObjectListBox->connect(ObjectListBox->onMouseLeave.getName(), [this]()
    {
        canScroll = true;
    });
    ObjectListBox->connect(ObjectListBox->onMouseEnter.getName(), [this]()
    {
        canScroll = false;
    });
}
void MapEditor::releaseSelectEntity()
{
    if (SelectedEntity)
    {
        SelectedEntity->removeComponents();
        SelectedEntity = nullptr;
    }
}
