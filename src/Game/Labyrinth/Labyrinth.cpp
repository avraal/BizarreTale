// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by Andrew Volski on 14.09.18.
//

#include <zconf.h>
#include <stack>
#include "Labyrinth.hpp"
Labyrinth::Labyrinth(const std::string &Name) : Level(Name)
{
    height = 19;
    width = 23;
    ImageDirectory = "";
    CurrentPathFile = "";
    ImagesFormats.push_back(".png");
    ImagesFormats.push_back(".jpg");
    CameraSpeed = 4.0f;
    showInfo = true;
    backGroundColor = sf::Color(42, 76, 61);
}
bool Labyrinth::prepareLevel(sf::RenderWindow &window)
{
    if (!findAllFiles(PathToImages, ImagesFormats))
    {
        return false;
    }
    Level::prepareLevel(window);
    drawTileMap();
    return true;
}
void Labyrinth::drawTileMap()
{
    std::vector<std::string> Tiles;
    std::vector<std::string> Formats;
    Formats.emplace_back(".png");
    findAllFiles(Tiles, Formats);
    for (us_int i = 0; i < height * width; i++)
    {
        TileMap.push_back(new CPrimitiveQuad());
    }
    us_int x = 0, y = 0;
    for (auto t : TileMap)
    {
        t->setPosition(x * 64, y  * 64);
        x++;
        if (x == width)
        {
            y++;
            x = 0;
        }
    }

    //draw horizontal lines
    for (us_int i = 0; i < height; i++)
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
    for (us_int i = 0; i < width; i++)
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
    auto walls = mazeGenerate();

    for (us_int i = 0; i < TileMap.size(); i++)
    {
        if (walls[i] == VISITED)
        {
            TileMap[i]->setIndex(VISITED);
        } else
        {
            TileMap[i]->setIndex(WALL);
        }
//        if (i % height == 0)
        {
//            std::cout << "" << std::endl;
        }
//        std::cout << TileMap[i]->getIndex() << " ";
    }
//    std::cout << "Width: " << width << std::endl;
//    std::cout << "Height: " << height << std::endl;
    for (us_int i = 0; i < TileMap.size(); i++)
    {
        if (TileMap[i]->getIndex() == VISITED)
        {
//            TileMap[i]->setPosition(-1000.f, -1000.f);
        }
    }
}
void Labyrinth::MouseCallbacks(sf::RenderWindow &window, sf::Event &event)
{
    if (event.type == sf::Event::MouseWheelScrolled)
    {
        ZoomViewAt(window, {event.mouseWheelScroll.x, event.mouseWheelScroll.y}, event.mouseWheelScroll.delta > 0 ? (1.0f / 1.1f) : 1.1f);
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
}
void Labyrinth::draw(sf::RenderWindow &window)
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
}
std::vector<us_int> Labyrinth::mazeGenerate()
{
    MazeData maze;
    maze.data = new us_int*[width];
    for (us_int i = 0; i < width; i++)
    {
        maze.data[i] = new us_int[height];
    }

    for (us_int i = 0; i < width; i++)
    {
        for (us_int j = 0; j < height; j++)
        {
            if (i % 2 != 0 && j % 2 != 0 && (i < width - 1 && j < height - 1))
            {
                maze.data[i][j] = CELL;
            }
            else
            {
                maze.data[i][j] = WALL;
            }
        }
    }

    std::stack<Point> path;
    Point startPoint {1, 1};
    Point currentPoint = startPoint;
    path.push(currentPoint);
    maze.data[currentPoint.x][currentPoint.y] = VISITED;
    int randomRange = 0;
    srand(static_cast<int>(time(NULL)));
    do
    {
        std::vector<Point> unvisitedNeighbor = getUnvisitedNeighbor(maze, currentPoint);
//        for (auto u : unvisitedNeighbor)
//        {
//            std::cout << u.x << " | " << u.y << std::endl;
//        }
        if (!unvisitedNeighbor.empty())
        {
            randomRange = rand() % unvisitedNeighbor.size();
            Point nextCell = unvisitedNeighbor[randomRange];
            maze.data = removeWall(currentPoint, nextCell, maze.data);
            currentPoint = nextCell;
            path.push(nextCell);
            maze.data[currentPoint.x][currentPoint.y] = VISITED;
            unvisitedNeighbor.clear();
        }
        else if (!path.empty())
        {
//            std::cout << "Go back (" << path.size() << ")" << std::endl;
            currentPoint = path.top();
            path.pop();
        } else
        {
//            std::cout << "Find random unvisited" << std::endl;
            std::vector<Point> unvisitedCells = getUnvisitedCells(width, height, maze);
            if (!unvisitedCells.empty())
            {
                randomRange = rand() % unvisitedCells.size();
                currentPoint = unvisitedCells[randomRange];
                unvisitedCells.clear();
            }
        }
//        std::cout << "" << std::endl;
//        sleep(3);
    }while(getUnvisitedCount(maze) > 0);
    showMaze(&maze);
    std::vector<us_int> Maze;
    for (us_int i = 0; i < width; i++)
    {
        for (us_int j = 0; j < height; j++)
        {
            Maze.push_back(maze.data[i][j]);
        }

    }
    for (us_int i = 0; i < width; i++)
    {
        delete [] maze.data[i];
    }
    delete [] maze.data;
    return Maze;
}
void Labyrinth::showMaze(MazeData *maze)
{
    std::cout << "Width: " << width << std::endl;
    std::cout << "Height: " << height << std::endl;
    for (us_int i = 0; i < width; i++)
    {
        for (us_int j = 0; j < height; j++)
        {
            std::cout << maze->data[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
int Labyrinth::getUnvisitedCount(MazeData maze)
{
    us_int count = 0;
    for (us_int i = 0; i < width; i++)
    {
        for (us_int j = 0; j < height; j++)
        {
            if (maze.data[i][j] != VISITED && maze.data[i][j] != WALL)
            {
                count++;
            }
//            count += maze.data[i][j] != VISITED;
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
//    Point *result = new Point[4];
    std::vector<Point> result;
    for (us_int i = 0; i < 4; i++)
    {
        if (d[i].x > 0 && d[i].x < width - 1 && d[i].y > 0 && d[i].y < height - 1)
        {
            us_int currentCell = maze.data[d[i].x][d[i].y];
            Point currentPoint = d[i];
            if (currentCell != WALL && currentCell != VISITED && currentCell != WAY)
            {
                result.push_back(currentPoint);
            }
        }
    }

//    std::cout << "Size: " << result.size() << std::endl;
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
//    std::cout << "Size: " << result.size() << std::endl;
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

