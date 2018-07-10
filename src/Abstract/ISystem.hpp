
// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by Andrew Volski on 10.07.18.
//

#ifndef BIZARRETALE_ISYSTEM_HPP
#define BIZARRETALE_ISYSTEM_HPP

class ISystem
{
public:
    virtual ~ISystem() = 0;

    //TODO: maybe add GameState
    virtual void Execute() = 0;
};

#endif //BIZARRETALE_ISYSTEM_HPP
