
// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by Andrew Volski on 25.07.18.
//

#ifndef BIZARRETALE_SUI_HPP
#define BIZARRETALE_SUI_HPP

#include <TGUI/Gui.hpp>

class UIWrapper
{
public:
    std::unique_ptr<tgui::Gui> gui;
    UIWrapper();
    virtual void Execute();
    virtual ~UIWrapper();
};

#endif //BIZARRETALE_SUI_HPP
