
// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by Andrew Volski on 10.07.18.
//

#include "LevelManager.hpp"
void LevelManager::registerLevel(const std::string &name)
{
    Level *l = new Level(Levels.size() + 1, name);
    registerLevel(l);
}
void LevelManager::registerLevel(Level *l)
{
    Levels.insert(std::pair<std::string, Level*>(l->getName(), l));
}
LevelManager::~LevelManager()
{
    for(auto l : Levels)
    {
        delete l.second;
    }
    Levels.clear();
}
void LevelManager::Execute()
{

}
LevelManager::LevelManager()
{

}
Level *LevelManager::changeLevelByName(const std::string &name)
{
    if(Levels.find(name) != Levels.end())
    {
        return Levels[name];
    }
    return nullptr;
}
