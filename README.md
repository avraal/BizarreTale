# BizarreTale
Simple constructor for gamedev
Guide for using BizarreTale Editor v. 0.3

## How to create a Singleton object:
```c++
SingletonClass &obj = SingletonClass::Instance();
```
### Other information for Singleton:
- Has private ctor and dtor
- Copy and move ctors has specificator **delete**

<br>

# IComponent
### Pattern: Entity-Component-System
Base abstract class for all Components  
Every Component has Name  
Has only one field with setters and getters for him
 
<br>

<br>

# IEntity
### Pattern: Entity-Component-System
Base abstract class for all Entity in game.  
Every Entity has a:
* Array of Components;
* World Position - position entity on level;
* Unique ID - on level;
* Unique Name - on level;
* Body - empty CPrimitiveQuad.

# CTile
### Pattern: Component
### Parent: CPrimitiveQuad

Basic Component for render.

<br>

# CPrimitiveQuad
### Pattern: Component
### Parents: sf::Drawable, sf::Transformable, IComponent

Represents array of vertex `(sf::VertexArray)`.

<br>

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
