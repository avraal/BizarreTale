
// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by Andrew Volski on 10.07.18.
//

#include "SLevelManager.hpp"
#include <algorithm>

void SLevelManager::registerLevel(std::shared_ptr<Level> l)
{
    Levels.insert(std::pair<std::string, std::shared_ptr<Level>>(l->getName(), l));
}
SLevelManager::~SLevelManager()
{
    Levels.clear();
}
void SLevelManager::Execute()
{

}
SLevelManager::SLevelManager()
{

}
std::shared_ptr<Level> SLevelManager::changeLevelByName(const std::string &name)
{
    if(Levels.find(name) != Levels.end())
    {
        return Levels[name];
    }
    return nullptr;
}
std::shared_ptr<Level> SLevelManager::loadLevel(const std::string &name)
{
    if (Levels.find(name) == Levels.end())
    {
        return nullptr;
    }
    return Levels.find(name)->second;
}
