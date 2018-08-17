
// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by Andrew Volski on 10.07.18.
//

#ifndef BIZARRETALE_ICOMPONENT_HPP
#define BIZARRETALE_ICOMPONENT_HPP

#include <string>
#include <memory>

class IEntity;
class IComponent : public std::enable_shared_from_this<IComponent>
{
protected:
    std::string Name;
    int id;
    std::shared_ptr<IEntity> entity;

public:
    IComponent();
    IComponent(int id, const std::string &name);
    virtual ~IComponent() = 0;
    virtual void release() = 0;
    virtual void Attach(std::shared_ptr<IEntity>);
    virtual std::string getName() const noexcept final;
    virtual int getId() const noexcept final;
    virtual std::shared_ptr<IEntity> getEntity();
};

#endif //BIZARRETALE_ICOMPONENT_HPP
