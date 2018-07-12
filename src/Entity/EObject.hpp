
// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by Andrew Volski on 12.07.18.
//

#ifndef BIZARRETALE_EOBJECT_HPP
#define BIZARRETALE_EOBJECT_HPP

#include "../Abstract/IEntity.hpp"

class EObject : public IEntity
{
public:
    //TODO: Add Level as parameter
    EObject();
    virtual ~EObject();
};

#endif //BIZARRETALE_EOBJECT_HPP
