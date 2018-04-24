# BizarreTale
Simple constuctor for gamedev

Guide for using BizarreTale Editor v. 0.1

## How to create a Singleton object:
```c++
SingletonClass &obj = SingletonClass::Instance();
```
### Other information for Singleton:
- Has private ctor and dtor
- Copy and move ctors has specificator **delete**

# MapIO
### Pattern: Singleton

It's a class, who is intendent writing and reading files.

Use LoadFromFile and SaveToFile to using his scope.
```c++
obj.SaveToFile("filename.format", objectContainer);
obj.LoadFromFile("filename.fromat", objectContainer);
```
# MapEditor
### Pattern: Singleton

Simple editor for game maps

Has a public fields:
- [ImageDirectory];
- [LuaDirectory];
- [initWindow].

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
> argv[0] = "BizarreTale" (11 sybmols)

#### Start:
After ImageDirectory identified, editor might be started
```c++
Editor.initWindow();
```
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

[ImageDirectory]: <https://github.com/avraal/BizarreTale/blob/master/README.md#imagedirectory>
[initWindow]: <https://github.com/avraal/BizarreTale/blob/master/README.md#start>
[LuaDirectory]: <https://github.com/avraal/BizarreTale/blob/master/README.md#luadirectory>
