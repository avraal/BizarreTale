// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by Andrew Volski on 26.09.18.
//

#ifndef DEMIURGE_ENTITYMANAGER_HPP
#define DEMIURGE_ENTITYMANAGER_HPPclea

#include <algorithm>
#include <map>
#include "../../Entity/IEntity.hpp"
#include "../../Util/GetClassName.hpp"

class EntityManager
{
private:
    EntityManager() {}
    ~EntityManager() {}

    static std::vector<IEntity*> Entities;
    static std::map<std::string, IEntity *(*)(us_int, const std::string&)> RegisteredMethods;
    static us_int currentId;

    static us_int getNextId();
public:
    EntityManager(const EntityManager &) = delete;
    EntityManager(EntityManager &&) = delete;
    EntityManager&operator=(const EntityManager &) = delete;
    EntityManager&operator=(EntityManager &&) = delete;

    static IEntity *getEntity(int id);
    static IEntity *Create(const std::string &TypeName, const std::string &objName);

    template <typename ERegisterabe>
    static void Register()
    {
        RegisteredMethods.insert({GetClassName::Get<ERegisterabe>(), &ERegisterabe::Create});
    }

    static bool Destroy(int id);

    static void ShowAll();

    static int getCount();
};

#endif //DEMIURGE_ENTITYMANAGER_HPP
