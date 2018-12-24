// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by Andrew Volski on 26.09.18.
//

#include <iostream>
#include "EntityManager.hpp"
#include "ComponentManager.hpp"

std::vector<std::shared_ptr<IEntity>> EntityManager::Entities;
std::map<std::string, std::function<std::shared_ptr<IEntity>(us_int, const std::string&)>> EntityManager::RegisteredEntities;

us_int EntityManager::currentId = 0;

void EntityManager::ShowAll()
{
    for (const auto &e : Entities)
    {
        std::cout << "id: " << e->getId() << " name: " << e->getName() << std::endl;
    }
}
bool EntityManager::Destroy(us_int id)
{
    int beforeSize = Entities.size();

    auto target = getEntity(id);

    if (!target)
    {
        std::cout << "Can\'t find object" << std::endl;
        return false;
    }

    ComponentManager::DestroyAllByEntityId(id);
    Entities.erase(std::remove(Entities.begin(), Entities.end(), target), Entities.end());
    target.reset();
    return beforeSize != Entities.size();
}

std::shared_ptr<IEntity> EntityManager::getEntity(us_int id)
{
    for (auto &e : Entities)
    {
        if (e->getId() == id)
        {
            return e;
        }
    }
    std::cout << "EntityManager returned nullptr" << std::endl;
    return nullptr;
}

std::shared_ptr<IEntity> EntityManager::getEntity(const std::string &name)
{
    for (auto &e : Entities)
    {
        if (e->getName() == name)
        {
            return e;
        }
    }
    std::cout << "EntityManager returned nullptr" << std::endl;
    return nullptr;
}

int EntityManager::getCount()
{
    return Entities.size();
}
us_int EntityManager::getNextId()
{
    return currentId++;
}