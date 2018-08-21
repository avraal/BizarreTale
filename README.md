# BizarreTale (Deprecated)
Simple constructor for gamedev
Guide for using BizarreTale Editor v. 0.3

## How to create a Singleton object:
```c++
SingletonClass &obj = SingletonClass::Instance();
```
### Other information for Singleton:
- Has private ctor and dtor
- Copy and move ctors has specificator **delete**


# IComponent
### Pattern: Entity-Component-System, Command
Base abstract class for all Components  
Every Component has Name  
Has only one field with setters and getters for him
 

# IEntity
### Pattern: Entity-Component-System
Base abstract class for all Entity in game.  
Every Entity has a:
* Array of Components;
* World Position - position entity on level;
* Unique ID - on level;
* Unique Name - on level;
* Body - empty CPrimitiveQuad.

# ISystem
### Pattern: Entity-Component-System
Base behaviour for all System. 

# LevelManager
### Parent: ISystem
Manage you levels, saved their by name in map.
If you're going to use some level, you must register him.
```cpp
levelManager->registerLevel(CurrentLevel);
``` 

# Level
**Now, he haven't Parent**  
This something, what have a game objects. Level can manipulate objects.  
Every level have a unique name, collection with game objects and draw-method.  
You can added new level like this:
```cpp
Level *CurrentLevel = new Level(0, "Test");
CurrentLevel->initGui(window);
...
while(window.isOpen())
{
    ...
    CurrentLevel->draw(window);
    ...
}
```
**ToDo:** in future, maybe remove id system for level, because every level have unique name.
If you want to create a new object:
```cpp
auto obj = new EObject(ImagePath);
CurrentLevel->addObject(obj);
```

After this, you can see you new object on display.

# EObject
### Parent: IEntity
Simple class for represent game objects.  
You can create a body for him. Just add path to image in ctor.  
```cpp
EObject *obj = new EObject(""); //this object haven't image
```
or
```cpp
EObject *obj = new EObject("image.png");
```


# CTile
## Pattern: Component  
## Parent: CPrimitiveQuad

Basic Component for render.

# CPrimitiveQuad
### Pattern: Component
### Parents: sf::Drawable, sf::Transformable, IComponent

Represents array of vertex `(sf::VertexArray)`.


# MapEditor
### Pattern: Singleton
### Parent: none

Simple editor for game maps

Public fields:
- [ImageDirectory]

Public methods:
- [initWindow]
- [LoadFromFile] (unused)
- [SaveToFile] (unused)

#### ImageDirectory
Identify of directory, where find images

Init directories:
```c++
Editor.ImageDirectory.clear();
Editor.ImageDirectory.append(argv[0]);
Editor.ImageDirectory = Editor.ImageDirectory.substr(0, Editor.ImageDirectory.size() - 11);
Editor.LuaDirectory = Editor.ImageDirectory;
Editor.ImageDirectory.append("Res/Images/");
Editor.LuaDirectory.append("Res/Lua/");
```
> argv[0] = "BizarreTale" (11 symbols)

#### Start:
After directories identified, editor might be started
```c++
Editor.initWindow();
```
#### [Unused]LoadFromFile:
Has a two parameters:
* `fileName` - where objects are load
* `obj` - container in which objects are loaded

This method start a new thread, which blocked other threads and call `LoadFromFile` from MapIO.

#### [Unused]SaveToFile:
Just like a `LoadFromFile` has a two parameters.

This method start a new thread, which blocked other threads and call `SaveToFile` from MapIO.

<br>

# MapIO (unused)
### Pattern: Singleton
### Parent: none

It's a class, who is writing and reading files.

Use LoadFromFile and SaveToFile to using his scope.
```c++
obj.SaveToFile("filename.format", objectContainer);
obj.LoadFromFile("filename.format", objectContainer);
```
<br>

[ImageDirectory]: <https://github.com/avraal/BizarreTale/blob/master/README.md#imagedirectory>
[initWindow]: <https://github.com/avraal/BizarreTale/blob/master/README.md#start>
[LoadFromFile]: <https://github.com/avraal/BizarreTale/blob/master/README.md#loadfromfile>
[SaveToFile]: <https://github.com/avraal/BizarreTale/blob/master/README.md#savetofile>
