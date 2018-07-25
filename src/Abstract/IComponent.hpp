
// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by Andrew Volski on 10.07.18.
//

#ifndef BIZARRETALE_ICOMPONENT_HPP
#define BIZARRETALE_ICOMPONENT_HPP

#include <string>

class IComponent
{
protected:
    std::string Name;
public:
    virtual ~IComponent() = 0;

    virtual void setName(const std::string &name) noexcept final;
    virtual std::string getName() const noexcept final;
};

#endif //BIZARRETALE_ICOMPONENT_HPP
