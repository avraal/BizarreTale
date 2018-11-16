# Demiurge Engine 0.4.5a
Simple engine for 2D games
Guide for using.  
Demiurge - it's Entity-Component-System (ECS) based engine.  

## Entity and EntityManager
Based unit of all game objects. Every entity has a list of unique identifiers components. You can't create entity without EntityManager, because constructor (ctor) and destructor (dtor) - has private access modifier.  
EntityManager - it's class, which can create, delete, etc. entity.

```cpp
EObject *Wall = static_cast<EObject*>(EntityManager::Create(GetClassName::Get<EObject>(), "Wall0"));
Wall->DoesSomeMethod();
addObject(Wall->getId());
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
This method released all components which linked with him.

## Component and ComponentManager
Based thing for interaction entity with entity. Every component has a unique id and id of entity to which his attached. Like Entity objects, component may created only on ComponentManager:
```cpp
Wall->body = static_cast<CDrawable *>(ComponentManager::Create(GetClassName::Get<CDrawable>(), Wall->getId(), "body"));
Wall->transform = static_cast<CTransform *>(ComponentManager::Create(GetClassName::Get<CTransform>(), Wall->getId(), "transform"));
``` 

In Create-method ComponentManager find entity by id and attach id of component to him. If entity not found, returned nullptr.  

## Level-based system
Every entity may have drawable components. For draw you may used draw-method. This method definition in every level. 
Life-cycle every level:
1. Register level in LevelManager
2. Load level  
2.1 Init ImageDirectory  
2.2 Init camera
3. Main loop (every frame)  
3.1 Handle event callbacks  
3.2 Draw

How you can create level? It's easy: create class and inherit from abstract class **Level**.
```cpp
class LTest : public Level
{
public:
    LTest(const std::string &name);
    virtual ~LTest() {}
    virtual bool prepareLevel(sf::RenderWindow &window) override;
    virtual void draw(sf::RenderWindow &window) override;
    virtual void MouseCallbacks(sf::RenderWindow &window, sf::Event &event) override;
    virtual void KeyBoardCallbacks(sf::RenderWindow &window, sf::Event &event) override;
};
```
You can stay ctor empty, like this:
```cpp
LTest::LTest(const std::string &name) : Level(name)
{
}
```
But you must know, in ctor of Level-class init base fields:
```
- Id - unique integer identifier. Generated automatically (Level::getNextId());
- Name - set from ctor parameter;
- ImageDirectory - empty by default. Path for folder with images;
- ImagesFromats - vector, which contained file formats when searched. By default added .png and .jpg formats;
- backgroundColor - color for background. By default is sf::Color::Black;
- UserInterface - wrapper for work with UI. Just init;
```

And register classes for EntityManager and ComponentManager:
```cpp
EntityManager::Register<EObject>();
ComponentManager::Register<CDrawable>();
ComponentManager::Register<CTransform>();
```

If you want register you class, ctor of you level-class - best idea.  
**prepareLevel** - method for prepared you components and objects in level

#### Registered level
```cpp
auto ltest = std::make_shared<LTest>("test-level");
levelManager->registerLevel(ltest);
```

#### Load level
```cpp
CurrentLevel = levelManager->loadLevel("test-level");
```

#### Init ImageDirectory
```cpp
CurrentLevel->ImageDirectory = this->ImageDirectory;
```

#### Init Camera
```cpp
CurrentLevel->setCamera(MainCamera);
```

#### Handle event callbacks
```cpp
CurrentLevel->MouseCallbacks(window, event);
CurrentLevel->KeyBoardCallbacks(window, event);
CurrentLevel->HandleGUIEvent(event);
```

#### Draw level
```cpp
CurrentLevel->draw(window);
```