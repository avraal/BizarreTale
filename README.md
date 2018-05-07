# BizarreTale
Simple constuctor for gamedev
(Guide version is depricated)
Guide for using BizarreTale Editor v. 0.1

## How to create a Singleton object:
```c++
SingletonClass &obj = SingletonClass::Instance();
```
### Other information for Singleton:
- Has private ctor and dtor
- Copy and move ctors has specificator **delete**

<br>

# MapIO
### Pattern: Singleton

It's a class, who is intendent writing and reading files.

Use LoadFromFile and SaveToFile to using his scope.
```c++
obj.SaveToFile("filename.format", objectContainer);
obj.LoadFromFile("filename.fromat", objectContainer);
```
<br>

# MapEditor
### Pattern: Singleton

Simple editor for game maps

Has a public fields:
- [ImageDirectory]
- [LuaDirectory]
- [initWindow]
- [LoadFromFile]

#### ImageDirectory
Identify of directory, where find images

#### LuaDirectory
Identify of directory, where find lua scripts

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
#### LoadFromFile:
Has a two parametres:
* `fileName` - where objects are load
* `obj` - container in which objects are loaded

This method start a new thread, which blocked other threads and call `LoadFromFile` from MapIO.

<br>

# ClassAnalyzer
### Pattern: Singleton

Checks size of classes and write it in file

Might be started before or after MapEditor
```c++
ca.start();
```
or

```c++
ca.start(true);
```

Method "start" has a default argument, which determine: print info in console or not. By default it's - **false**.

> But this class have a defect: if i add a new class to project, ClassAnalyzer will be read file as file which already has information about new class. In this case, ClassAnalyzer write garbage.

<br>

# LuaScripts
### Pattern: none

Use for set contact with Lua scripts. For use, needed add LuaScripts object in class

Start:
```c++
script.Create();
script.DoFile("PathToLuaScript.lua");
```

If you want to call lua function, you needed a register her
```c++
script.RegisterConstant<lua_CFunction>(reinterpret_cast<lua_CFunction>(&YouClass::YouHandler), "YouFunction");
```

Method 'RegisterConstant' - is a specialized template. For example:
```c++
template<>
void LuaScripts::RegisterConstant<lua_CFunction>(lua_CFunction value, char *constName)
{
    lua_pushcfunction(lua_state, value);
    lua_setglobal(lua_state, constName);
}
```
Except him, this class have another one specialized template - method `Push`. For example:
```c++
template<>
void LuaScripts::Push<int>(int value)
{
    lua_pushinteger(lua_state, value);
}
```
Except `int`, he have a templates for next types:
- char*
- const char*
- bool
- double

Where 'YouHandler' - is a c++ method this like style
```c++
int YouClass::YouHandler(lua_State*)
{
  //...
  return 0;
}
```
> After this you might use your dirty methods

Now LuaScripts have 3 methods related to work with files:
* `SaveToFile` - writing collection of objects to file
* `LoadFromFile` - reading objects from file
* `getTableSize` - finds lua table in file and returns her size



[ImageDirectory]: <https://github.com/avraal/BizarreTale/blob/master/README.md#imagedirectory>
[initWindow]: <https://github.com/avraal/BizarreTale/blob/master/README.md#start>
[LuaDirectory]: <https://github.com/avraal/BizarreTale/blob/master/README.md#luadirectory>
[LoadFromFile]: <https://github.com/avraal/BizarreTale/blob/master/README.md#loadfromfile>
