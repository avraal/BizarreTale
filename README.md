# Demiurge Engine 0.4[pre](https://github.com/avraal/BizarreTale/blob/master/README.md#marks)1a  
Simple engine for 2D games
Guide for using.  
Demiurge - it's Entity-Component-System (ECS) based engine.  

## Entity and EntityManager
Based unit of all game objects. Every entity has a list of unique identifiers components. You can't create entity without EntityManager, because constructor (ctor) and destructor (dtor) - has private access modifier.  
EntityManager - it's class, which can create, delete, etc. entity.

```cpp
auto player = static_cast<IEntity*>(EntityManager::Create("Hero"));
if (!player)
{
    return 1;
}
```

This code created a new entity - player with name "Hero". **Create** - is a static method of class EntityManager, which created new object of class IEntity, added to vector and returned him.  
Every entity has a unique identifier. id has generated on constructor call:
```cpp
IEntity *ie = new IEntity(getNextId(), name);
```
**getNextId()** - private method for incremented static filed **currentId**

List of EntityManager fields:
- getEntity(int id) - find entity in vector by id, and returned him or nullptr;
- Create(const std::string &name) - create new entity with name;
- Destroy(int id) - destroyed entity by id;
- ShowAll() - print id and name of all entities;
- getCount() - return count of entity

## Component and ComponentManager
Based thing for interaction entity with entity. Every component has a unique id and id of entity to which his attached. Like Entity objects, component may created only on ComponentManager:
```cpp
if (!ComponentManager::Create(player->getId(), "Position"))
{
    return 1;
}
``` 

Unlike Create method of EntityManager, ComponentManager returned bool variable. In this method ComponentManager find entity by id and attach id of component to him. If entity not found, returned false.  
List of EntityManager fields:
- getComponent(int id) - find component by id and returned him or nullptr;
- Create(int entityId, const std::string &name) - create new component with name and attach to entity;
- Destroy(int id) - destroyed component by id;

<hr>

# Marks  
**pre** - it's a mark of prepare to deploy new system  
