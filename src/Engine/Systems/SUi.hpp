
// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by Andrew Volski on 25.07.18.
//

#ifndef BIZARRETALE_SUI_HPP
#define BIZARRETALE_SUI_HPP

#include <TGUI/Gui.hpp>
#include "ISystem.hpp"

class SUi : public ISystem
{
private:
public:
//    tgui::Gui *gui;
    std::unique_ptr<tgui::Gui> gui;
    SUi();
    virtual void Execute();
    virtual ~SUi();
};

#endif //BIZARRETALE_SUI_HPP
