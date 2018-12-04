// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by Andrew Volski on 14.09.18.
//

#include <zconf.h>
#include <stack>
#include "Labyrinth.hpp"
#include "../../Engine/Systems/Managers/EntityManager.hpp"
#include "../../Engine/Systems/Managers/ComponentManager.hpp"
#include "../../Engine/Util/GetClassName.hpp"
#include "../../Engine/Entity/EObject.hpp"
#include <thread>
#include <SFML/System/Thread.hpp>
Labyrinth::Labyrinth(const std::string &Name) : Level(Name)
{
    tileSizeY = 99;
    tileSizeX = 99;
    CameraSpeed = 14.0f;
    showInfo = true;
}
bool Labyrinth::prepareLevel(sf::RenderWindow &window)
{
    std::cout << getName() << " prepare method" << std::endl;
    if (!Level::prepareLevel(window))
    {
        return false;
    }
    UserInterface->gui->add(infoPanel);

    //    drawTileMap();

    std::thread LaunchDraw(&Labyrinth::drawTileMap, this);
    LaunchDraw.detach();

    return true;
}
void Labyrinth::drawTileMap()
{
    us_int **walls = mazeGenerate();

    for (us_int i = 0; i < tileSizeX; i++)
    {
        for (us_int j = 0; j < tileSizeY; j++)
        {
            if (walls[i][j] != VISITED)
            {
                if (guard.try_lock())
                {
                    auto tile = std::static_pointer_cast<EObject>(
                            EntityManager::Create(GetClassName::Get<EObject>()));
                    tile->transform = std::static_pointer_cast<CTransform>(
                            ComponentManager::Create(GetClassName::Get<CTransform>(), tile->getId(), "transform"));

                    tile->body = std::static_pointer_cast<CDrawable>(
                            ComponentManager::Create(GetClassName::Get<CDrawable>(), tile->getId(), "body"));
                    tile->setPosition(sf::Vector2i(j * TILE_SIZE_DEFAULT, i * TILE_SIZE_DEFAULT));
                    addObject(tile->getId());
                    TileIds.push_back(tile->getId());
                    guard.unlock();
                }
            }
        }
    }
    std::this_thread::yield();

    for (auto i : TileIds)
    {
        auto entity = std::static_pointer_cast<EObject>(EntityManager::getEntity(i));
        for (auto j : entity->ComponentsId)
        {
            auto component = std::static_pointer_cast<CDrawable>(ComponentManager::getComponent(j));
            component->setCanDraw(true);
        }
    }
    //horizontal lines
    sf::Color lineColor = sf::Color(42, 76, 61);
//    sf::Color lineColor = sf::Color::White;
    for (float j = 0; j <= tileSizeX; j++)
    {
        sf::Vertex line[] =
                {
                        sf::Vertex({0, j * TILE_SIZE_DEFAULT}, lineColor),
                        sf::Vertex({0.f + (tileSizeY * TILE_SIZE_DEFAULT), j * TILE_SIZE_DEFAULT}, lineColor)
                };
        LineGrid.emplace_back(std::pair<sf::Vertex, sf::Vertex>(line[0], line[1]));
    }
    //vertical lines
    for (float i = 0; i <= tileSizeY; i++)
    {
        sf::Vertex line[] =
                {
                        sf::Vertex({i * TILE_SIZE_DEFAULT, 0}, lineColor),
                        sf::Vertex({i * TILE_SIZE_DEFAULT, 0.f + (tileSizeX * TILE_SIZE_DEFAULT)}, lineColor)
                };
        LineGrid.emplace_back(std::pair<sf::Vertex, sf::Vertex>(line[0], line[1]));
    }

    for (us_int i = 0; i < tileSizeX; i++)
    {
        delete[] walls[i];
    }
    delete[] walls;
}
void Labyrinth::MouseCallbacks(sf::RenderWindow &window, sf::Event &event)
{
    if (event.type == sf::Event::MouseWheelScrolled)
    {
        ZoomViewAt(window, {event.mouseWheelScroll.x, event.mouseWheelScroll.y},
                   event.mouseWheelScroll.delta > 0 ? (1.0f / 1.1f) : 1.1f);
    }
}
void Labyrinth::KeyBoardCallbacks(sf::RenderWindow &window, sf::Event &event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        switch (event.key.code)
        {
            case sf::Keyboard::Escape:
            {
                std::cout << "Last fps: " << fps << std::endl;
                window.close();
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
        }
    }
}
void Labyrinth::HandleGUIEvent(sf::Event &event)
{
    Level::HandleGUIEvent(event);
}
void Labyrinth::draw(sf::RenderWindow &window)
{
    Level::draw(window);
    for (auto g : LineGrid)
    {
        sf::Vertex line[] =
                {
                        g.first,
                        g.second
                };
        window.draw(line, 2, sf::Lines);
    }
    infoFPSLabel->setText("FPS: " + std::to_string((us_int) fps));
    infoObjCount->setText("ObjCount: " + std::to_string(ObjectIds.size()));
    infoDrawableComponentCount->setText("DrawableComponentCount: " + std::to_string(DrawableComponents.size()));
}

us_int **Labyrinth::mazeGenerate()
{
    MazeData maze;
    maze.data = new us_int *[tileSizeX];
    for (us_int i = 0; i < tileSizeX; i++)
    {
        maze.data[i] = new us_int[tileSizeY];
    }

    for (us_int i = 0; i < tileSizeX; i++)
    {
        for (us_int j = 0; j < tileSizeY; j++)
        {
            if (i % 2 != 0 && j % 2 != 0 && (i < tileSizeX - 1 && j < tileSizeY - 1))
            {
                maze.data[i][j] = CELL;
            } else
            {
                maze.data[i][j] = WALL;
            }
        }
    }

    std::stack<Point> path;
    Point startPoint{1, 1};
    Point currentPoint = startPoint;
    path.push(currentPoint);
    maze.data[currentPoint.x][currentPoint.y] = VISITED;
    int randomRange = 0;
    srand(static_cast<int>(time(NULL)));
    do
    {
        std::vector<Point> unvisitedNeighbor = getUnvisitedNeighbor(maze, currentPoint);

        if (!unvisitedNeighbor.empty())
        {
            randomRange = rand() % unvisitedNeighbor.size();
            Point nextCell = unvisitedNeighbor[randomRange];
            maze.data = removeWall(currentPoint, nextCell, maze.data);
            currentPoint = nextCell;
            path.push(nextCell);
            maze.data[currentPoint.x][currentPoint.y] = VISITED;
            unvisitedNeighbor.clear();
        } else if (!path.empty())
        {
            //            std::cout << "Go back (" << path.size() << ")" << std::endl;
            currentPoint = path.top();
            path.pop();
        } else
        {
            //            std::cout << "Find random unvisited" << std::endl;
            std::vector<Point> unvisitedCells = getUnvisitedCells(tileSizeX, tileSizeY, maze);
            if (!unvisitedCells.empty())
            {
                randomRange = rand() % unvisitedCells.size();
                currentPoint = unvisitedCells[randomRange];
                unvisitedCells.clear();
            }
        }
        //        std::cout << "" << std::endl;
        //        sleep(3);
    } while (getUnvisitedCount(maze) > 0);
    showMaze(&maze);
    return maze.data;
}
void Labyrinth::showMaze(MazeData *maze)
{
    std::cout << "Width: " << tileSizeX << std::endl;
    std::cout << "Height: " << tileSizeY << std::endl;
    for (us_int i = 0; i < tileSizeX; i++)
    {
        for (us_int j = 0; j < tileSizeY; j++)
        {
            std::cout << maze->data[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
int Labyrinth::getUnvisitedCount(MazeData maze)
{
    us_int count = 0;
    for (us_int i = 0; i < tileSizeX; i++)
    {
        for (us_int j = 0; j < tileSizeY; j++)
        {
            count += maze.data[i][j] != VISITED && maze.data[i][j] != WALL;
        }
    }
    return count;
}
std::vector<Labyrinth::Point> Labyrinth::getUnvisitedNeighbor(Labyrinth::MazeData maze, Point p)
{
    Point up = {p.x, p.y - 2};
    Point rt = {p.x + 2, p.y};
    Point dw = {p.x, p.y + 2};
    Point lt = {p.x - 2, p.y};

    Point d[4] = {dw, rt, up, lt};
    std::vector<Point> result;
    for (us_int i = 0; i < 4; i++)
    {
        if (d[i].x > 0 && d[i].x < tileSizeX - 1 && d[i].y > 0 && d[i].y < tileSizeY - 1)
        {
            us_int currentCell = maze.data[d[i].x][d[i].y];
            Point currentPoint = d[i];
            if (currentCell != WALL && currentCell != VISITED && currentCell != WAY)
            {
                result.push_back(currentPoint);
            }
        }
    }

    return result;
}
us_int **Labyrinth::removeWall(Labyrinth::Point currentPoint, Labyrinth::Point nextCell, us_int **pInt)
{
    int xDiff = nextCell.x - currentPoint.x;
    int yDiff = nextCell.y - currentPoint.y;
    int addX;
    int addY;
    Point target;

    addX = (xDiff != 0) ? (xDiff / abs(xDiff)) : 0;
    addY = (yDiff != 0) ? (yDiff / abs(yDiff)) : 0;

    target.x = currentPoint.x + addX;
    target.y = currentPoint.y + addY;
    pInt[target.x][target.y] = VISITED;

    return pInt;
}

std::vector<Labyrinth::Point> Labyrinth::getUnvisitedCells(us_int width, us_int height, Labyrinth::MazeData maze)
{
    std::vector<Point> result;
    for (us_int i = 0; i < width; i++)
    {
        for (us_int j = 0; j < height; j++)
        {
            if ((maze.data[i][j] != WALL) && (maze.data[i][j] != VISITED))
            {
                result.push_back({i, j});
            }
        }
    }
    return result;
}

void Labyrinth::ZoomViewAt(sf::RenderWindow &window, sf::Vector2i pixel, float zoom)
{
    const sf::Vector2f beforeCoord{window.mapPixelToCoords(pixel)};
    MainCamera->zoom(zoom);
    const sf::Vector2f afterCoord{window.mapPixelToCoords(pixel)};
    const sf::Vector2f offsetCoord{beforeCoord - afterCoord};
    MainCamera->move(offsetCoord);
}
void Labyrinth::loadGui(sf::RenderWindow &window)
{
    infoFPSLabel = tgui::Label::create();
    infoFPSLabel->getRenderer()->setTextColor(sf::Color::White);
    infoFPSLabel->setTextSize(INFO_PANEL_TEXT_SIZE);

    infoObjCount = tgui::Label::copy(infoFPSLabel);
    infoObjCount->setPosition(infoFPSLabel->getPosition().x, infoFPSLabel->getPosition().y + INFO_PANEL_TEXT_SIZE + 2);

    infoDrawableComponentCount = tgui::Label::copy(infoFPSLabel);
    infoDrawableComponentCount->setPosition(infoObjCount->getPosition().x,
                                            infoObjCount->getPosition().y + INFO_PANEL_TEXT_SIZE + 2);

    infoPanel = tgui::Panel::create({200, 100});
    infoPanel->setPosition(window.getSize().x - infoPanel->getSize().x, 0);
    infoPanel->getRenderer()->setBackgroundColor(sf::Color(0, 0, 0, 128));

    infoPanel->add(infoFPSLabel);
    infoPanel->add(infoObjCount);
    infoPanel->add(infoDrawableComponentCount);
}
Labyrinth::~Labyrinth()
{
    //    for (us_int i = 0; i < tileSizeX; i++)
    //    {
    //        delete[] TilesIds[i];
    //    }
    //    delete[] TilesIds;
}
