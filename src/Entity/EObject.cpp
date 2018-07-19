
// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by Andrew Volski on 12.07.18.
//

#include "EObject.hpp"
#include "../CPrimitiveQuad.hpp"
#include "../Level.hpp"
#include "../CTile.h"

EObject::~EObject()
{

}
EObject::EObject(const std::string &ImagePath)
{
    if(!ImagePath.empty())
    {
        body = std::make_shared<CTile>("body", ImagePath, getPosition());
        Components.push_back(std::dynamic_pointer_cast<IComponent>(body));
    }
}