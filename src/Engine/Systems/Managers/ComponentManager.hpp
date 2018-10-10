// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by Andrew Volski on 26.09.18.
//

#ifndef DEMIURGE_COMPONENTMANAGER_HPP
#define DEMIURGE_COMPONENTMANAGER_HPP

#include <stack>
#include <vector>
#include <map>
#include "../../Components/IComponent.hpp"
#include "../../Util/GetClassName.hpp"

class ComponentManager
{
private:
    ComponentManager() {}
    ~ComponentManager() {}

    static std::vector<IComponent*> Components;
    static std::map<std::string, IComponent *(*)(us_int id, us_int, const std::string&)> RegisteredMethods;
    static int currentId;
    static int getNextId();

public:
    ComponentManager(const ComponentManager &) = delete;
    ComponentManager(ComponentManager &&) = delete;
    ComponentManager&operator=(const ComponentManager &) = delete;
    ComponentManager&operator=(ComponentManager &&) = delete;

    static IComponent * Create(const std::string &TypeName, int entityId, const std::string &objName);
    static bool Destroy(int compId);

    template <typename CRegisterable>
    static void Register()
    {
        RegisteredMethods.insert({GetClassName::Get<CRegisterable>(), &CRegisterable::Create});
    }

    static IComponent *getComponent(int id);

    static void ShowComponents();
};

#endif //DEMIURGE_COMPONENTMANAGER_HPP
