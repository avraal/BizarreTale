
// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by Andrew Volski on 10.07.18.
//

#ifndef BIZARRETALE_LEVEL_HPP
#define BIZARRETALE_LEVEL_HPP

#include <string>
#include <vector>
#include <memory>

class TileEntity;

class Level final
{
private:
    int Id;
    std::string Name;
    std::vector<std::shared_ptr<TileEntity>> ObjList;
public:
    Level() = delete;
    Level(int id, const std::string &Name);
    Level(const Level&);
    Level(const Level&&);
    ~Level();

    void addObject(std::shared_ptr<TileEntity> te);
    size_t getObjCount();
    std::shared_ptr<TileEntity> getObject(int index);
    std::vector<std::shared_ptr<TileEntity>> &getAllObjects();
};

#endif //BIZARRETALE_LEVEL_HPP
