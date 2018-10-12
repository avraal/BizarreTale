# Demiurge Engine 0.4.3
Simple engine for 2D games
Guide for using.  
Demiurge - it's Entity-Component-System (ECS) based engine.  

## Entity and EntityManager
Based unit of all game objects. Every entity has a list of unique identifiers components. You can't create entity without EntityManager, because constructor (ctor) and destructor (dtor) - has private access modifier.  
EntityManager - it's class, which can create, delete, etc. entity.

```cpp
EObject *Wall = static_cast<EObject*>(EntityManager::Create(GetClassName::Get<EObject>(), "Wall0"));
if (!Wall)
{
    //exit
    return 1;
}
Wall->DoesSomeMethod();
```

This code created a new game object - wall with name "Wall0". **Create** - is a static method of class EntityManager, which created new object by class name, added to vector and returned him.
If your class wants to be created in this method, you must registered your class like this:
```cpp
EntityManager::Register<YouClass>();
```
When **YouClass** inherited from **EObject** or **IEntity** with **ERegisterable< YouClass >**
Every entity has a unique identifier. Id has generated on constructor call.  
You can destroy any object by id:
```cpp
EntityManager::Destroy(Wall->getId());
```
This method released all components which linked with him

###### Deprecated:
```
List of EntityManager fields:
- getEntity(int id) - find entity in vector by id, and returned him or nullptr;
- Create(const std::string &name) - create new entity with name;
- Clear(int id) - destroyed entity by id;
- ShowAll() - print id and name of all entities;
- getCount() - return count of entity
```
###### Deprecated:
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
- Clear(int id) - destroyed component by id;