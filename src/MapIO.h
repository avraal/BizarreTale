//
// Created by andrew on 16.04.18.
//

#ifndef BIZARRETALE_MAPIO_H
#define BIZARRETALE_MAPIO_H

#include <fstream>
#include <memory>
#include <cstring>
#include "MapEntity.h"

class MapIO
{
private:
    MapIO() {}
    ~MapIO() {}

public:
    MapIO(MapIO const&) = delete;
    MapIO &operator=(MapIO const&) = delete;
    static MapIO &Instance()
    {
        static MapIO mio;
        return mio;
    }


    void SaveToFile(std::string fileName, std::vector<std::shared_ptr<MapEntity>> &obj, std::vector<std::shared_ptr<MapEntity>> tiles);
    void LoadFromFIle(std::string fileName, std::vector<std::shared_ptr<MapEntity>> &obj);
};

#endif //BIZARRETALE_MAPIO_H
