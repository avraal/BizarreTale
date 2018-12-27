// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by Andrew Volski on 26.09.18.
//

#include <iostream>
#include "ComponentManager.hpp"
#include "EntityManager.hpp"
std::vector<std::shared_ptr<IComponent>> ComponentManager::Components;
std::map<std::string, std::function<std::shared_ptr<IComponent>(us_int id, us_int, const std::string&)>> ComponentManager::RegisteredComponents;

int ComponentManager::currentId = 0;


std::shared_ptr<IComponent> ComponentManager::getComponent(us_int id)
{
    for (auto &c : Components)
    {
        if (c->getId() == id)
        {
            return c;
        }
    }
    std::cout << "Can\'t find component" << std::endl;
    return nullptr;
}

std::shared_ptr<IComponent> ComponentManager::getComponent(const std::string &name)
{
    for (auto &c : Components)
    {
        if (c->getName() == name)
        {
            return c;
        }
    }
    std::cout << "Can\'t find component" << std::endl;
    return nullptr;
}

bool ComponentManager::Destroy(us_int compId)
{
    us_int entityId = getComponent(compId)->entityId;
    return Destroy(compId, entityId);
}

bool ComponentManager::Destroy(us_int compId, us_int entityId)
{
    auto beforeSize = Components.size();

    for (auto it = Components.begin(); it != Components.end(); )
    {
        if ((*it)->id == compId && (*it)->entityId == entityId)
        {
            getComponent(compId).reset();
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
    for (const auto &c : Components)
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
        comp.reset();
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
            getComponent((*it)->id).reset();
            it = Components.erase(it);
        }
        else
        {
            ++it;
        }
    }
}