// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by andrew on 16.04.18.
//

#include "ClassAnalizer.h"
void ClassAnalizer::start(bool showDebug)
{
    std::vector<ClassData> readData;
    ClassData data;

    std::ofstream toFile("Info.dat", std::ios_base::app);
    if (!toFile)
    {
        std::cerr << "[ClassAnalizer | toFile] " << "File not found" << std::endl;
    } else
    {
        toFile.write((char *) &data, sizeof(data));
    }
    toFile.close();

    std::ifstream fromFile("Info.dat", std::ios_base::in);
    if (!fromFile)
    {
        std::cerr << "[ClassAnalizer | fromFile] " << "File not found" << std::endl;
    } else
    {
        while (fromFile.read((char *) &data, sizeof(data)))
        {
            readData.push_back(data);
        }
    }
    fromFile.close();

    if (showDebug)
    {
        std::cout << "Before: " << std::endl;
        for (auto d : readData)
        {
            std::cout << "Date: " << std::ctime(&d.time);
            std::cout << "MapEntity: " << d._entity << std::endl;
            std::cout << "MapEditor: " << d._editor << std::endl;
            std::cout << "MapIO:" << d._map << std::endl;
            std::cout << "ClassAnalizer: " << d._anal << std::endl;
            std::cout << "------------------" << std::endl;
        }
    }
    if (readData.size() >= 2)
    {
        auto f = readData[readData.size() - 1];
        auto s = readData[readData.size() - 2];
        if (f._editor == s._editor && f._entity == s._entity &&
            f._map    == s._map    && f._anal   == s._anal)
        {
            if (showDebug)
                std::cout << "Remove element" << std::endl;
            readData.pop_back();
        }
    }

    if (showDebug)
    {
        std::cout << "After: " << std::endl;
        for (auto d : readData)
        {
            std::cout << "Date: " << std::ctime(&d.time);
            std::cout << "MapEntity: " << d._entity << std::endl;
            std::cout << "MapEditor: " << d._editor << std::endl;
            std::cout << "MapIO:" << d._map << std::endl;
            std::cout << "ClassAnalizer: " << d._anal << std::endl;
            std::cout << "------------------" << std::endl;
        }
    }
    toFile.open("Info.dat", std::ios_base::trunc);
    if (!toFile)
    {
        std::cerr << "[ClassAnalizer | toFile] " << "File not found" << std::endl;
    } else
    {
        for (auto d : readData)
        {
            toFile.write((char *) &d, sizeof(d));
        }
    }
    toFile.close();
}
