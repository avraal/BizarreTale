
// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by Andrew Volski on 10.07.18.
//

#include "SLevelManager.hpp"

void SLevelManager::registerLevel(Level *l)
{
    Levels.insert(std::pair<std::string, Level*>(l->getName(), l));
}
SLevelManager::~SLevelManager()
{
    for(auto l : Levels)
    {
        delete l.second;
    }
    Levels.clear();
}
void SLevelManager::Execute()
{

}
SLevelManager::SLevelManager()
{

}
Level *SLevelManager::changeLevelByName(const std::string &name)
{
    if(Levels.find(name) != Levels.end())
    {
        return Levels[name];
    }
    return nullptr;
}
