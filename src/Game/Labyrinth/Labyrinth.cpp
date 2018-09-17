// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by Andrew Volski on 14.09.18.
//

#include "Labyrinth.hpp"
Labyrinth::Labyrinth(const std::string &Name) : Level(Name)
{
    height = 11;
    width = 11;
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
    mazeGenerate();
    return true;
}
void Labyrinth::drawTileMap()
{
    std::vector<std::string> Tiles;
    std::vector<std::string> Formats;
    Formats.emplace_back(".png");
    findAllFiles(Tiles, Formats);
    for (us_int i = 1; i <= height * width; i++)
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
void Labyrinth::MouseCallbacks(sf::RenderWindow &window, sf::Event &event)
{
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
void Labyrinth::mazeGenerate()
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

    Point startPoint {1, 1};
    Point currentPoint = startPoint;
    maze.data[currentPoint.x][currentPoint.y] = VISITED;
//    currentPoint = {1, 2};
//    maze.data[currentPoint.x][currentPoint.y] = VISITED;

//    do
//    {
        Point *unvisited = getUnvisitedNeighbor(maze, currentPoint);
        for (us_int i = 0; i < 4; i++)
        {
            std::cout << unvisited[i].x << " | " << unvisited[i].y << std::endl;
        }
//        return;

//    }while(getUnvisited(maze) > 0);
    showMaze(&maze);
}
void Labyrinth::showMaze(MazeData *maze)
{
    for (us_int i = 0; i < width; i++)
    {
        for (us_int j = 0; j < height; j++)
        {
            std::cout << maze->data[i][j];
        }
        std::cout << std::endl;
    }
}
int Labyrinth::getUnvisited(MazeData maze)
{
    us_int count = 0;
    for (us_int i = 0; i < width; i++)
    {
        for (us_int j = 0; j < height; j++)
        {
            if (maze.data[i][j] != VISITED)
            {
                count++;
            }
//            count += maze.data[i][j] != VISITED;
        }
    }
    return 0;
}
Labyrinth::Point *Labyrinth::getUnvisitedNeighbor(Labyrinth::MazeData maze, Point p)
{
    Point up = {p.x, p.y - 2};
    Point rt = {p.x + 2, p.y};
    Point dw = {p.x, p.y + 2};
    Point lt = {p.x - 2, p.y};

    Point d[4] = {dw, rt, up, lt};
    Point *result = new Point[4];
    us_int size = 0;
    for (us_int i = 0; i < 4; i++)
    {
        if (d[i].x > 0 && d[i].x < width && d[i].y > 0 && d[i].y < height)
        {
            us_int currentCell = maze.data[d[i].x][d[i].y];
            Point currentPoint = d[i];
            if (currentCell != WALL && currentCell != VISITED && currentCell != WAY)
            {
                result[size] = currentPoint;
                size++;
            }
        }
    }
    std::cout << "Size: " << size << std::endl;
    return result;
}
