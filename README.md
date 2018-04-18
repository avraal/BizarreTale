# BizarreTale
Simple constuctor for gamedev

Guide for using BizarreTale Editor v. 0.1

## How to create a Singleton object:
```c++
SingletonClass &obj = SingletonClass::Instance();
```

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

Has a:
- [CurrentDirectory];
- [initWindow]

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
```c++
Editor.initWindow();
```

[CurrentDirectory]: <https://github.com/avraal/BizarreTale/blob/master/README.md#currentdirectory>
[initWindow]: <https://github.com/avraal/BizarreTale/blob/master/README.md#start>
