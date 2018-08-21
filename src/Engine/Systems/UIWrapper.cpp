
// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by Andrew Volski on 25.07.18.
//

#include "UIWrapper.hpp"
UIWrapper::UIWrapper()
{
    gui = nullptr;
}
void UIWrapper::Execute()
{
    gui->draw();
}
UIWrapper::~UIWrapper()
{
    //deleted in dtor Level
}
