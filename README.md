# BizarreTale
Simple constuctor for gamedev

Guide for using BizarreTale Editor v. 0.1

# How create a Singleton object:
SingletonClass &obj = SingletonClass::Instance();

# MapIO
Pattern: Singleton

It's a class, who is intendent writing and reading files.

Use LoadFromFile and SaveToFile to using his scope.
```sh
obj.SaveToFile("filename.format", objectContainer);
obj.LoadFromFile("filename.fromat", objectContainer);
```
# MapEditor
Pattern: Singleton

Has a public fields:
- CurrentDirectory - to identify directory, where find images;

Init CurrentDirectory
```sh
Editor.CurrentDirectory.clear();
Editor.CurrentDirectory.append(argv[0]);
Editor.CurrentDirectory = Editor.CurrentDirectory.substr(0, Editor.CurrentDirectory.size() - 11);
```
> argv[0] = "BizarreTale" (11 sybmols)

Start editor
```sh
Editor.initWindow();
```
