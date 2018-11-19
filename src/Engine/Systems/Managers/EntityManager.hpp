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

class EntityManager
{
private:
    EntityManager() {}
    ~EntityManager() {}

    friend class Level;

    static std::vector<std::shared_ptr<IEntity>> Entities;
    static std::map<std::string, std::function<std::shared_ptr<IEntity>(us_int, const std::string&)>> RegisteredMethods;
    static us_int currentId;

    static us_int getNextId();
    static bool Destroy(int id);

public:
    EntityManager(const EntityManager &) = delete;
    EntityManager(EntityManager &&) = delete;
    EntityManager&operator=(const EntityManager &) = delete;
    EntityManager&operator=(EntityManager &&) = delete;

    static std::shared_ptr<IEntity> getEntity(us_int id);
    static std::shared_ptr<IEntity> Create(const std::string &TypeName, const std::string &objName);

    template <typename ERegisterable>
    static void Register()
    {
        RegisteredMethods.insert({GetClassName::Get<ERegisterable>(), &ERegisterable::Create});
    }


    static void ShowAll();

    static int getCount();
};

#endif //DEMIURGE_ENTITYMANAGER_HPP