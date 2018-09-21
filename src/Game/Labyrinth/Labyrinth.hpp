// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by Andrew Volski on 14.09.18.
//

#ifndef DEMIURGE_LABYRINTH_HPP
#define DEMIURGE_LABYRINTH_HPP

#include "../../Engine/Level.hpp"

class Labyrinth : public Level
{
private:

    struct Point
    {
        us_int x;
        us_int y;
    };

    struct MazeData
    {
        us_int **data;
    };

    enum MazeCellType {CELL, WALL, VISITED, WAY};

    bool showInfo;
    float CameraSpeed;

    std::vector<std::string> ImagesFormats;                         //all supported image formats
    std::vector<std::string> PathToImages;                          //all images
    std::vector<std::pair<sf::Vertex, sf::Vertex>> LineGrid;        //grid of lines

    void drawTileMap();
    std::vector<us_int> mazeGenerate();
    void showMaze(MazeData *maze);
    std::string CurrentPathFile;                                    //path to image, which added to map

    us_int width;
    us_int height;

    std::vector<CPrimitiveQuad*> TileMap;                           //draw grid for add new objects

public:
    Labyrinth(const std::string &Name);
    virtual ~Labyrinth() {}

    virtual bool prepareLevel(sf::RenderWindow &window) override;
    virtual void MouseCallbacks(sf::RenderWindow &window, sf::Event &event) override;
    void ZoomViewAt(sf::RenderWindow &window, sf::Vector2i pixel, float zoom);
    virtual void draw(sf::RenderWindow &window) override;
    virtual void KeyBoardCallbacks(sf::RenderWindow &window, sf::Event &event) override;
    virtual void HandleGUIEvent(sf::Event &event) override;
    int getUnvisitedCount(MazeData maze);
    std::vector<Point> getUnvisitedNeighbor(Labyrinth::MazeData maze, Point p);
    us_int **removeWall(Point currentPoint, Point nextCell, us_int **pInt);
    std::vector<Point> getUnvisitedCells(us_int width, us_int height, MazeData maze);
    void showMazeCoords(std::vector<us_int> coords);
};

#endif //DEMIURGE_LABYRINTH_HPP
