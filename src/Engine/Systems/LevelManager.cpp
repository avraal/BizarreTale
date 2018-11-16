
// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by Andrew Volski on 10.07.18.
//

#include "LevelManager.hpp"
#include <algorithm>

void LevelManager::registerLevel(std::shared_ptr<Level> l)
{
    Levels.insert(std::pair<std::string, std::shared_ptr<Level>>(l->getName(), l));
}
LevelManager::~LevelManager()
{
    Levels.clear();
}
LevelManager::LevelManager()
{

}
std::shared_ptr<Level> LevelManager::loadLevel(const std::string &name)
{
    if (Levels.find(name) == Levels.end())
    {
        return nullptr;
    }
    std::cout << "Load " << name << std::endl;
    return Levels.find(name)->second;
}
