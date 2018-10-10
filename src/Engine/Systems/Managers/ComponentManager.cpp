// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by Andrew Volski on 26.09.18.
//

#include <iostream>
#include "ComponentManager.hpp"
#include "EntityManager.hpp"
std::vector<IComponent*> ComponentManager::Components;
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
        return c;
    }
    return nullptr;
//    auto target = EntityManager::getEntity(entityId);
//
//    if (!target)
//    {
//        return false;
//    }
//    IComponent *component = new IComponent(getNextId(), entityId, objName);
//    target->ComponentsId.push_back(component->getId());
//    Components.push_back(component);
//    return true;
}
IComponent *ComponentManager::getComponent(int id)
{
    auto target = std::find_if(Components.begin(), Components.end(), [id](IComponent *ie)
    {
        return ie->id == id;
    });
    if (!*target || (*target)->getId() != id)
    {
        std::cout << "Can\'t find component" << std::endl;
        return nullptr;
    }
    return *target;
}
bool ComponentManager::Destroy(int compId)
{
    int beforeSize = Components.size();

    auto target = getComponent(compId);
    if (!target)
    {
        std::cout << "Can\'t find object" << std::endl;
        return false;
    }
    auto entity = EntityManager::getEntity(target->entityId);
    if (!entity)
    {
        std::cout << "Can\'t find entity" << std::endl;
        return false;
    }
    std::cout << "Release " << target->getName() << " component" << std::endl;
    entity->ComponentsId.erase(std::remove(entity->ComponentsId.begin(), entity->ComponentsId.end(), compId), entity->ComponentsId.end());
    Components.erase(std::remove(Components.begin(), Components.end(), target), Components.end());
    delete target;
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