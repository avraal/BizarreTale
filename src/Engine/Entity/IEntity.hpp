
// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by Andrew Volski on 10.07.18.
//

#ifndef BIZARRETALE_IENTITY_HPP
#define BIZARRETALE_IENTITY_HPP

#include <vector>
#include <memory>
#include <forward_list>
#include <algorithm>
#include "../Components/CPrimitiveQuad.hpp"

class Level;
class IComponent;
class CTile;
class IEntity
{
protected:
    us_int Id;
    sf::Vector2f Position;
    std::string Name;
//    std::vector<std::weak_ptr<IComponent>> Components;
    std::vector<std::shared_ptr<IComponent>> Components;

    static us_int currentId;
    static us_int getNextId();

public:
    IEntity();
    IEntity(const IEntity&);
    IEntity&operator=(const IEntity&);
    virtual us_int GetId()                               const noexcept final;
    virtual void setName(const std::string &name)           noexcept final;
    virtual std::string getName()                     const noexcept final;
    virtual void setPosition(float x, float y) = 0;
    virtual void setPosition(const sf::Vector2f &position) = 0;
    void addComponent(std::shared_ptr<IComponent> component);
    void removeComponent(us_int compId);
    void removeComponents();
    sf::Vector2f getPosition() const;
    std::shared_ptr<IComponent> getComponent(us_int id);
    std::shared_ptr<IComponent> getComponent(const std::string &Name);
    std::vector<std::shared_ptr<CPrimitiveQuad>> getDrawable();

    template <class T>
    std::shared_ptr<T> getComponent(const std::string &Name)
    {
        for (auto c : Components)
        {
//            if (c.lock()->getName() == Name)
            if (c->getName() == Name)
            {
                return std::dynamic_pointer_cast<T>(c);
            }
        }
        return nullptr;
    }

    inline bool operator==(const IEntity &rhs) const
    {
        return this->Id == rhs.Id;
    }

    inline bool operator!=(const IEntity &rhs) const
    {
        return this->Id != rhs.Id;
    }

    inline bool operator==(const IEntity *rhs) const
    {
        return this->Id == rhs->Id;
    }

    inline bool operator!=(const IEntity *rhs) const
    {
        return this->Id != rhs->Id;
    }

    virtual ~IEntity() = 0;
};

#endif //BIZARRETALE_IENTITY_HPP
