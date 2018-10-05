// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by Andrew Volski on 26.09.18.
//

#ifndef DEMIURGE_ENTITYMANAGER_HPP
#define DEMIURGE_ENTITYMANAGER_HPPclea

#include <algorithm>
#include "../../Entity/IEntity.hpp"

class EntityManager
{
private:
    EntityManager() {}
    ~EntityManager() {}

    static std::vector<IEntity*> Entities;
    static int currentId;

    static int getNextId();
public:
    EntityManager(const EntityManager &) = delete;
    EntityManager(EntityManager &&) = delete;
    EntityManager&operator=(const EntityManager &) = delete;
    EntityManager&operator=(EntityManager &&) = delete;

    static IEntity *getEntity(int id);
    static IEntity *Create(const std::string &name);

    static bool Destroy(int id);

    static void ShowAll();

    static int getCount();
};

#endif //DEMIURGE_ENTITYMANAGER_HPP
