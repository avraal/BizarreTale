// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by Andrew Volski on 10.10.18.
//

#ifndef DEMIURGE_GETCLASSNAME_HPP
#define DEMIURGE_GETCLASSNAME_HPP

#include <string>

template <class T>
std::string getClassName()
{
    std::string tmp = typeid(T).name();
    int position = 0;
    for (int i = 0; i < tmp.length(); i++)
    {
        if (isdigit(tmp.at(i)))
        {
            position = i;
        }
    }
    tmp.erase(0, position + 1);
    return tmp;
}

#endif //DEMIURGE_GETCLASSNAME_HPP
