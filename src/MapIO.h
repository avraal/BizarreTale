// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by andrew on 16.04.18.
//

#ifndef BIZARRETALE_MAPIO_H
#define BIZARRETALE_MAPIO_H

#include <fstream>
#include <memory>
#include <cstring>
#include <list>
#include "TileEntity.h"
#include "json.hpp"

using json = nlohmann::json;

class MapIO
{
private:

    MapIO()
    {
    }
    ~MapIO()
    {
    }

public:
    MapIO(MapIO const &) = delete;
    MapIO &operator=(MapIO const &) = delete;
    static MapIO &Instance()
    {
        static MapIO mio;
        return mio;
    }

    void SaveToFile(std::string fileName, std::vector<std::shared_ptr<TileEntity>> obj);
    void LoadFromFile(std::string fileName, std::vector<std::shared_ptr<TileEntity>> &obj);
};

#endif //BIZARRETALE_MAPIO_H
