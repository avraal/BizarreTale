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
- [CurrentDirectory];
- [initWindow].

#### CurrentDirectory
Identify of directory, where find images

Init:
```c++
Editor.CurrentDirectory.clear();
Editor.CurrentDirectory.append(argv[0]);
Editor.CurrentDirectory = Editor.CurrentDirectory.substr(0, Editor.CurrentDirectory.size() - 11);
```
> argv[0] = "BizarreTale" (11 sybmols)

#### Start:
After CurrentDirectory identified, editor might be started
```c++
Editor.initWindow();
```
# ClassAnalizer
### Pattern: Singleton

Checks size of classes and write it in file

Might be started before or after MapEditor
```c++
ca.start();
```
Method "start" has a default argument, which determine: print info in console or not. By default it's - **false**.

> But this class have a defect: if i add a new class to project, ClassAnalizer will be read file as file which already has information about new class. In this case, ClassAnalizer write garbage.

[CurrentDirectory]: <https://github.com/avraal/BizarreTale/blob/master/README.md#currentdirectory>
[initWindow]: <https://github.com/avraal/BizarreTale/blob/master/README.md#start>
