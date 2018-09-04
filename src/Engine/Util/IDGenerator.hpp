
// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by Andrew Volski on 13.08.18.
//

#ifndef BIZARRETALE_IDGENERATOR_HPP
#define BIZARRETALE_IDGENERATOR_HPP

#include <iostream>
#include "../CONST_DEFINITIONS.h"

class IDGenerator final
{
private:
    static us_int currentId;

public:
    IDGenerator() = delete;
    IDGenerator(const IDGenerator &) = delete;
    IDGenerator(const IDGenerator &&) = delete;
    IDGenerator &operator=(const IDGenerator &) = delete;
    IDGenerator &operator=(const IDGenerator &&) = delete;

    static us_int getNextId();
};

#endif //BIZARRETALE_IDGENERATOR_HPP
