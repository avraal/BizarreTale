// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by Andrew Volski on 26.09.18.
//

#ifndef DEMIURGE_ENTITYMANAGER_HPP
#define DEMIURGE_ENTITYMANAGER_HPP

#include <algorithm>
#include <map>
#include <functional>
#include "../../Entity/IEntity.hpp"
#include "../../Util/GetClassName.hpp"
class ComponentManager;
class EntityManager final
{
private:
    friend class Level;

    static std::vector<std::shared_ptr<IEntity>> Entities;
    static std::map<std::string, std::function<std::shared_ptr<IEntity>(us_int, const std::string&)>> RegisteredEntities;
    static us_int currentId;

    static us_int getNextId();
    static bool Destroy(us_int id);

public:
    EntityManager() {}
    ~EntityManager() {}

    EntityManager(const EntityManager &) = delete;
    EntityManager(EntityManager &&) = delete;
    EntityManager&operator=(const EntityManager &) = delete;
    EntityManager&operator=(EntityManager &&) = delete;

    static std::shared_ptr<IEntity> getEntity(us_int id);
    static std::shared_ptr<IEntity> getEntity(const std::string &name);

    template <typename E>
    static std::shared_ptr<E> Create(std::string objName = "")
    {
        const std::string TypeName = getClassName<E>();
        auto it = RegisteredEntities.find(TypeName);
        if (it != RegisteredEntities.end())
        {
            us_int id = getNextId();
            if (objName.empty())
            {
                objName = "obj" + std::to_string(id);
            }
            auto ie = it->second(id, objName);
            Entities.push_back(ie);
            ie->init();
            return std::static_pointer_cast<E>(ie);
        }
        return nullptr;
    }

    template <typename ERegisterable>
    static void Register()
    {
        RegisteredEntities.insert({getClassName<ERegisterable>(), &ERegisterable::Create});
    }

    static void ShowAll();

    static int getCount();
};

#endif //DEMIURGE_ENTITYMANAGER_HPP