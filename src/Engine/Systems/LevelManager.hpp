
// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by Andrew Volski on 10.07.18.
//

#ifndef BIZARRETALE_LEVELMANAGER_HPP
#define BIZARRETALE_LEVELMANAGER_HPP

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
    void registerLevel(std::shared_ptr<Level> l);
    std::shared_ptr<Level> changeLevelByName(const std::string &name);
    std::shared_ptr<Level> loadLevel(const std::string &name);
    ~LevelManager();
};

#endif //BIZARRETALE_LEVELMANAGER_HPP
