
// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by Andrew Volski on 10.07.18.
//

#ifndef DEMIURGE_ICOMPONENT_HPP
#define DEMIURGE_ICOMPONENT_HPP

#include <string>
#include <memory>
#include "../CONST_DEFINITIONS.hpp"

class IComponent;

template <typename T>
class CRegisterable
{
protected:
    friend class ComponentManager;
    static IComponent *Create(us_int id, us_int entityId, const std::string &name)
    {
        return new T(id, entityId, name);
    }
};

class IComponent
{
private:
    friend class ComponentManager;
protected:
    IComponent(us_int id, us_int entityId, const std::string &name);
    virtual ~IComponent() = 0;
    us_int id;
    us_int entityId;
    std::string name;

public:
    IComponent() = delete;

    virtual us_int getId() const noexcept final;
    virtual us_int getEntityId() const noexcept final;
    virtual const std::string & getName() const noexcept final;
};

#endif //DEMIURGE_ICOMPONENT_HPP
