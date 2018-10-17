// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by Andrew Volski on 26.09.18.
//

#include <iostream>
#include "EntityManager.hpp"
#include "ComponentManager.hpp"

std::vector<IEntity*> EntityManager::Entities;
std::map<std::string, IEntity *(*)(us_int, const std::string&)> EntityManager::RegisteredMethods;

us_int EntityManager::currentId = 0;

IEntity * EntityManager::Create(const std::string &TypeName, const std::string &objName)
{
    auto it = RegisteredMethods.find(TypeName);
    if (it != RegisteredMethods.end())
    {
        auto ie = it->second(getNextId(), objName);
        Entities.push_back(ie);
        return ie;
    }
    return nullptr;
}

void EntityManager::ShowAll()
{
    for (auto e : Entities)
    {
        std::cout << "id: " << e->getId() << " name: " << e->getName() << std::endl;
    }
}
bool EntityManager::Destroy(int id)
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
    delete target;
    return beforeSize != Entities.size();
}
IEntity *EntityManager::getEntity(int id)
{
    for (auto e : Entities)
    {
        if (e->getId() == id)
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