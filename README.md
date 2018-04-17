# BizarreTale
Simple constuctor for gamedev

Guide for using BizarreTale Editor v. 0.1

# How create a Singleton object:
SingletonClass &obj = SingletonClass::Instance();

# MapIO
Pattern: Singleton
it's a class, who is intendent writing and reading files.

Use LoadFromFile and SaveToFile to using his scope.
```sh
obj.SaveToFile("filename.format", objectContainer);
obj.LoadFromFile("filename.fromat", objectContainer);
```
