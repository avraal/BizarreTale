//
// Created by andrew on 16.04.18.
//

#ifndef BIZARRETALE_CLASSANALIZER_H
#define BIZARRETALE_CLASSANALIZER_H

#include <chrono>
#include <fstream>
#include "MapEditor.h"

class ClassAnalyzer
{
private:
    ClassAnalyzer() {}
    ~ClassAnalyzer() {}

    struct ClassData
    {
        long time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        size_t _entity = sizeof(MapEntity);
        size_t _editor = sizeof(MapEditor);
        size_t _map    = sizeof(MapIO);
        size_t _anal   = sizeof(ClassAnalyzer);
    };

public:
    void start(bool showDebug = false);
    ClassAnalyzer (ClassAnalyzer const&) = delete;
    ClassAnalyzer (ClassAnalyzer const &&) = delete;
    ClassAnalyzer &operator=(ClassAnalyzer const&) = delete;
    static ClassAnalyzer &Instance()
    {
        static ClassAnalyzer ca;
        return ca;
    }
};

#endif //BIZARRETALE_CLASSANALIZER_H
