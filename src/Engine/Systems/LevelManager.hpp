
// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by Andrew Volski on 10.07.18.
//

#ifndef DEMIURGE_LEVELMANAGER_HPP
#define DEMIURGE_LEVELMANAGER_HPP

#include <vector>
#include <memory>
#include <map>
#include "../Level.hpp"

class LevelManager
{
private:
    std::map<std::string, std::shared_ptr<Level>> Levels;
public:
    LevelManager();
    ~LevelManager();
    void registerLevel(std::shared_ptr<Level> l);
    std::shared_ptr<Level> loadLevel(const std::string &name);
};

#endif //DEMIURGE_LEVELMANAGER_HPP
