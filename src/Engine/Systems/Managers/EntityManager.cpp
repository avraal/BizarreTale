// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by Andrew Volski on 26.09.18.
//

#include <iostream>
#include "EntityManager.hpp"
#include "ComponentManager.hpp"

std::vector<IEntity*> EntityManager::Entities;
std::map<std::string, IEntity *(*)(int, const std::string&)> EntityManager::RegisteredMethods;

int EntityManager::currentId = 0;

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
    auto target = std::find_if(Entities.begin(), Entities.end(), [id](IEntity *ie)
    {
        return ie->id == id;
    });
    if (!*target || (*target)->getId() != id)
    {
        std::cout << "Can\'t find object" << std::endl;
        return nullptr;
    }
    return *target;
}
int EntityManager::getCount()
{
    return Entities.size();
}
int EntityManager::getNextId()
{
    return currentId++;
}