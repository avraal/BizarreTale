
// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by Andrew Volski on 25.07.18.
//

#ifndef DEMIURGE_UIWRAPPER_HPP
#define DEMIURGE_UIWRAPPER_HPP

#include <TGUI/Gui.hpp>

class UIWrapper
{
public:
    std::unique_ptr<tgui::Gui> gui;
    UIWrapper();
    virtual void Execute();
    virtual ~UIWrapper();
};

#endif //DEMIURGE_UIWRAPPER_HPP
