// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by Andrew Volski on 26.09.18.
//

#ifndef DEMIURGE_COMPONENTMANAGER_HPP
#define DEMIURGE_COMPONENTMANAGER_HPP

#include <stack>
#include "../../Components/IComponent.hpp"

class ComponentManager
{
private:
    ComponentManager() {}
    ~ComponentManager() {}
public:
    ComponentManager(const ComponentManager &manager)       = delete;
    ComponentManager(ComponentManager &&manager)            = delete;
    ComponentManager&operator=(const ComponentManager &)    = delete;
    ComponentManager&operator=(ComponentManager &&)         = delete;

    

    static ComponentManager &Instance()
    {
        static ComponentManager *instance = new ComponentManager();
        return *instance;
    }
};

#endif //DEMIURGE_COMPONENTMANAGER_HPP
