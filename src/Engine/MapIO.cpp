// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by andrew on 16.04.18.
//

#include <thread>
#include <deque>
#include "MapIO.h"

void MapIO::SaveToFile(std::string fileName, std::vector<std::shared_ptr<CTile>> obj)
{
    std::cout << "Preparing to write..." << std::endl;

}
void MapIO::LoadFromFile(std::string fileName, std::vector<std::shared_ptr<CTile>> &obj)
{
    std::cout << "Preparing to read..." << std::endl;
}
