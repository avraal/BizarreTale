// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by Andrew Volski on 26.09.18.
//

#include <iostream>
#include "ComponentManager.hpp"
#include "EntityManager.hpp"
std::vector<IComponent*> ComponentManager::Components;
std::map<std::string, IComponent *(*)(us_int, us_int, const std::string&)> ComponentManager::RegisteredMethods;

int ComponentManager::currentId = 0;

IComponent * ComponentManager::Create(const std::string &TypeName, int entityId, const std::string &objName)
{
    auto target = EntityManager::getEntity(entityId);
    if (!target)
    {
        return nullptr;
    }
    auto it = RegisteredMethods.find(TypeName);
    if (it != RegisteredMethods.end())
    {
        auto c = it->second(getNextId(), entityId, objName);
        Components.push_back(c);
        target->ComponentsId.push_back(c->id);
        return c;
    }
    return nullptr;
}
IComponent *ComponentManager::getComponent(int id)
{
    auto target = std::find_if(Components.begin(), Components.end(), [id](IComponent *ie)
    {
        return ie->id == id;
    });
    if (!*target || (*target)->getId() != id)
    {
//        std::cout << "Can\'t find component" << std::endl;
        return nullptr;
    }
    return *target;
}
bool ComponentManager::Destroy(us_int compId)
{
    us_int entityId = getComponent(compId)->entityId;
    return Destroy(compId, entityId);
}

bool ComponentManager::Destroy(us_int compId, us_int entityId)
{
    us_int beforeSize = Components.size();

    for (auto it = Components.begin(); it != Components.end(); )
    {
        if ((*it)->id == compId && (*it)->entityId == entityId)
        {
            delete getComponent(compId);
            it = Components.erase(it);
            break;
        } else
        {
            ++it;
        }
    }

    auto target = EntityManager::getEntity(entityId);
    target->ComponentsId.erase(std::remove(target->ComponentsId.begin(), target->ComponentsId.end(), compId), target->ComponentsId.end());

    return beforeSize != Components.size();
}
int ComponentManager::getNextId()
{
    return currentId++;
}
void ComponentManager::ShowComponents()
{
    for (auto c : Components)
    {
        std::cout << "id: " << c->getId() << " name: " << c->getName() << std::endl;
    }
}
void ComponentManager::DestroyAll()
{
    for (auto it = Components.begin(); it != Components.end(); )
    {
        auto comp = getComponent((*it)->id);
        auto entity = EntityManager::getEntity(comp->entityId);
        entity->ComponentsId.erase(std::remove(entity->ComponentsId.begin(), entity->ComponentsId.end(), comp->id), entity->ComponentsId.end());
        delete comp;
        it = Components.erase(it);
    }
}
void ComponentManager::DestroyAllByEntityId(us_int entityId)
{
    auto target = EntityManager::getEntity(entityId);
    for (auto it = Components.begin(); it != Components.end(); )
    {
        if ((*it)->entityId == entityId)
        {
            target->ComponentsId.erase(std::remove(target->ComponentsId.begin(), target->ComponentsId.end(), (*it)->id), target->ComponentsId.end());
            delete getComponent((*it)->id);
            it = Components.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

