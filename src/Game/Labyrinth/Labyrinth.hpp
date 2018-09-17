// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by Andrew Volski on 14.09.18.
//

#ifndef BIZARRETALE_LABYRINTH_HPP
#define BIZARRETALE_LABYRINTH_HPP

#include "../../Engine/Level.hpp"

class Labyrinth : public Level
{
private:

    struct MazeData
    {
        us_int **data;
    };

    struct Point
    {
        us_int x;
        us_int y;
    };

    enum MazeCellType {CELL, WALL, VISITED, WAY};

    bool showInfo;
    float CameraSpeed;

    std::vector<std::string> ImagesFormats;                         //all supported image formats
    std::vector<std::string> PathToImages;                          //all images
    std::vector<std::pair<sf::Vertex, sf::Vertex>> LineGrid;        //grid of lines

    void drawTileMap();
    void mazeGenerate();
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
    virtual void draw(sf::RenderWindow &window) override;
    virtual void KeyBoardCallbacks(sf::RenderWindow &window, sf::Event &event) override;
    virtual void HandleGUIEvent(sf::Event &event) override;
    int getUnvisited(MazeData maze);
    Point *getUnvisitedNeighbor(Labyrinth::MazeData maze, Point p);
};

#endif //BIZARRETALE_LABYRINTH_HPP
