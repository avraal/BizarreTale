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
#include "Components/CTile.h"

class MapIO
{
private:

    MapIO()
    {
    }
    virtual ~MapIO()
    {
    }

public:
    MapIO(MapIO const&) = delete;
    MapIO(MapIO&&) = delete;
    MapIO &operator=(MapIO const&) = delete;
    MapIO &operator=(MapIO&&) = delete;

    static MapIO &Instance()
    {
        static MapIO *mio = new MapIO();
        return *mio;
    }

    void SaveToFile(std::string fileName, std::vector<std::shared_ptr<CTile>> obj);
    void LoadFromFile(std::string fileName, std::vector<std::shared_ptr<CTile>> &obj);
};

#endif //BIZARRETALE_MAPIO_H
