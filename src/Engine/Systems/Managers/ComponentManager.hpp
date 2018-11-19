// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by Andrew Volski on 26.09.18.
//

#ifndef DEMIURGE_COMPONENTMANAGER_HPP
#define DEMIURGE_COMPONENTMANAGER_HPP

#include <stack>
#include <vector>
#include <functional>
#include <map>
#include "../../Components/IComponent.hpp"
#include "../../Util/GetClassName.hpp"

class ComponentManager
{
private:
    ComponentManager() {}
    ~ComponentManager() {}

    static std::vector<std::shared_ptr<IComponent>> Components;
    static std::map<std::string, std::function<std::shared_ptr<IComponent>(us_int id, us_int, const std::string&)>> RegisteredMethods;
    static int currentId;
    static int getNextId();

public:
    ComponentManager(const ComponentManager &) = delete;
    ComponentManager(ComponentManager &&) = delete;
    ComponentManager&operator=(const ComponentManager &) = delete;
    ComponentManager&operator=(ComponentManager &&) = delete;

    static std::shared_ptr<IComponent> Create(const std::string &TypeName, int entityId, const std::string &objName);
    static bool Destroy(us_int compId, us_int entityId);
    static bool Destroy(us_int compId);

    template <typename CRegisterable>
    static void Register()
    {
        RegisteredMethods.insert({GetClassName::Get<CRegisterable>(), &CRegisterable::Create});
    }

    static std::shared_ptr<IComponent> getComponent(us_int id);

    static void ShowComponents();
    static void DestroyAll();
    static void DestroyAllByEntityId(us_int entityId);
};

#endif //DEMIURGE_COMPONENTMANAGER_HPP