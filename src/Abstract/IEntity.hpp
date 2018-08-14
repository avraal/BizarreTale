
// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by Andrew Volski on 10.07.18.
//

#ifndef BIZARRETALE_IENTITY_HPP
#define BIZARRETALE_IENTITY_HPP

#include <vector>
#include <memory>
#include "../CPrimitiveQuad.hpp"

class Level;
class IComponent;
class CTile;
class IEntity
{
protected:
    int Id;
    sf::Vector2f Position;
    std::string Name;
    std::vector<std::weak_ptr<IComponent>> Components;

    static int currentId;
    static int getNextId();

    template <class T, class U>
    std::weak_ptr<T> static_pointer_cast(std::weak_ptr<U> const &rhs)
    {
        return std::static_pointer_cast<T>(std::shared_ptr<U>(rhs));
    }
public:
    IEntity();
    IEntity(const IEntity&);
    IEntity&operator=(const IEntity&);
    virtual int GetId()                               const noexcept final;
    virtual void setName(const std::string &name)           noexcept final;
    virtual std::string getName()                     const noexcept final;
    virtual void setPosition(float x, float y) = 0;
    virtual void setPosition(const sf::Vector2f &position) = 0;
    void addComponent(std::shared_ptr<IComponent> component);
    sf::Vector2f getPosition()                        const;
    std::shared_ptr<IComponent> getComponent(int id);
    std::shared_ptr<IComponent> getComponent(const std::string &Name);
    std::vector<std::shared_ptr<CPrimitiveQuad>> getDrawable();

    template <class T>
    std::shared_ptr<T> getComponent(const std::string &Name)
    {
        for (auto c : Components)
        {
            if (c.lock()->getName() == Name)
            {
                return std::dynamic_pointer_cast<T>(c.lock());
            }
        }
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
