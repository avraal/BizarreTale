
// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by Andrew Volski on 10.07.18.
//

#ifndef BIZARRETALE_LEVELMANAGER_HPP
#define BIZARRETALE_LEVELMANAGER_HPP

#include <vector>
#include <memory>
#include "../Abstract/ISystem.hpp"
#include "../Level.hpp"

class LevelManager : public ISystem
{
private:
    std::vector<Level> Levels;
public:
    virtual void Execute ();
};

#endif //BIZARRETALE_LEVELMANAGER_HPP
