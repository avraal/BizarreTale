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
#include "EntityManager.hpp"
#include "../../Components/IComponent.hpp"
#include "../../Util/GetClassName.hpp"
class ComponentManager final
{
private:
    static std::vector<std::shared_ptr<IComponent>> Components;
    static std::map<std::string, std::function<std::shared_ptr<IComponent>(us_int id, us_int, const std::string&)>> RegisteredComponents;
    static int currentId;
    static int getNextId();

public:
    ComponentManager() {}
    ~ComponentManager() {}
    ComponentManager(const ComponentManager &) = delete;
    ComponentManager(ComponentManager &&) = delete;
    ComponentManager&operator=(const ComponentManager &) = delete;
    ComponentManager&operator=(ComponentManager &&) = delete;

    template <typename C>
    static std::shared_ptr<C> Create(us_int entityId, std::string compName = "")
    {
        auto target = EntityManager::getEntity(entityId);
        if (!target)
        {
            return nullptr;
        }
        const std::string TypeName = getClassName<C>();
        auto it = RegisteredComponents.find(TypeName);
        if (it != RegisteredComponents.end())
        {
            us_int id = getNextId();
            if (compName.empty())
            {
                compName = "comp" + std::to_string(id);
            }
            auto c = it->second(getNextId(), entityId, compName);
            Components.push_back(c);
            target->ComponentsId.push_back(c->id);
            return std::static_pointer_cast<C>(c);
        }
        return nullptr;
    }

    static bool Destroy(us_int compId, us_int entityId);
    static bool Destroy(us_int compId);

    template <typename CRegisterable>
    static void Register()
    {
        RegisteredComponents.insert({getClassName<CRegisterable>(), &CRegisterable::Create});
    }

    static std::shared_ptr<IComponent> getComponent(us_int id);
    static std::shared_ptr<IComponent> getComponent(const std::string &name);

    static void ShowComponents();
    static void DestroyAll();
    static void DestroyAllByEntityId(us_int entityId);
};

#endif //DEMIURGE_COMPONENTMANAGER_HPP