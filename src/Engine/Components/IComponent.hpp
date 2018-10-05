
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

class IEntity;
class IComponent : public std::enable_shared_from_this<IComponent>
{
private:
    IComponent(us_int id, us_int entityId, const std::string &name);
    virtual ~IComponent() {}
protected:
    us_int id;
    us_int entityId;
    std::string name;

public:
    IComponent() = delete;
    friend class ComponentManager;
    virtual void release()  = 0;
    virtual void Attach(std::shared_ptr<IEntity>);
    virtual us_int getId() const noexcept final;
    virtual const std::string & getName() const noexcept final;
    virtual std::shared_ptr<IEntity> getEntity();

    inline bool operator==(const IComponent *rhs) const
    {
        return this->id == rhs->id;
    }

    friend std::ostream&operator<<(std::ostream &os, const IComponent &c);
};

#endif //DEMIURGE_ICOMPONENT_HPP
