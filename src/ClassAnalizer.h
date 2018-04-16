//
// Created by andrew on 16.04.18.
//

#ifndef BIZARRETALE_CLASSANALIZER_H
#define BIZARRETALE_CLASSANALIZER_H

#include <chrono>
#include <fstream>
#include "MapEditor.h"

class ClassAnalizer
{
private:
    ClassAnalizer() {}
    ~ClassAnalizer() {}

    struct ClassData
    {
        long time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        size_t _entity = sizeof(MapEntity);
        size_t _editor = sizeof(MapEditor);
    };

public:
    void start();
    ClassAnalizer (ClassAnalizer const&) = delete;
    ClassAnalizer (ClassAnalizer const &&) = delete;
    ClassAnalizer &operator=(ClassAnalizer const&) = delete;
    static ClassAnalizer &Instance()
    {
        static ClassAnalizer ca;
        return ca;
    }
};

#endif //BIZARRETALE_CLASSANALIZER_H
