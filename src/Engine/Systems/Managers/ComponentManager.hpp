// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by Andrew Volski on 26.09.18.
//

#ifndef DEMIURGE_COMPONENTMANAGER_HPP
#define DEMIURGE_COMPONENTMANAGER_HPP

#include <stack>
#include <vector>
#include "../../Components/IComponent.hpp"

class ComponentManager
{
private:
    ComponentManager() {}
    ~ComponentManager() {}

    static std::vector<IComponent*> Components;
    static int currentId;
    static int getNextId();

public:
    ComponentManager(const ComponentManager &) = delete;
    ComponentManager(ComponentManager &&) = delete;
    ComponentManager&operator=(const ComponentManager &) = delete;
    ComponentManager&operator=(ComponentManager &&) = delete;

    static bool Create(int entityId, const std::string &name);
    static bool Destroy(int compId);

    static IComponent *getComponent(int id);

    static void ShowComponents();
};

#endif //DEMIURGE_COMPONENTMANAGER_HPP
