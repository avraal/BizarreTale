
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
    std::vector<IComponent*> Components;
    CPrimitiveQuad *body;

    static int currentId;

    static int getNexId();
public:
    IEntity();

    virtual int GetId()                               const noexcept final;
    virtual void setName(const std::string &name)           noexcept final;
    virtual std::string getName()                     const noexcept final;
    void setPosition(float x, float y);
    void setPosition(const sf::Vector2f &position);
    void addComponent(IComponent *component);
    sf::Vector2f getPosition()                        const;
    CPrimitiveQuad *getBody();
    IComponent *getComponent(int id);
    std::vector<CPrimitiveQuad*> getDrawable();

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
