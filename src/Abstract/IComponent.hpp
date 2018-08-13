
// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by Andrew Volski on 10.07.18.
//

#ifndef BIZARRETALE_ICOMPONENT_HPP
#define BIZARRETALE_ICOMPONENT_HPP

#include <string>
class IEntity;
class IComponent
{
protected:
    std::string Name;
    int id;
    IEntity *entity;
public:

    IComponent(IEntity *entity, int id, const std::string &name);
    virtual ~IComponent() = 0;

    virtual std::string getName() const noexcept final;
    virtual int getId() const noexcept final;
    virtual IEntity *getEntity();
};

#endif //BIZARRETALE_ICOMPONENT_HPP
