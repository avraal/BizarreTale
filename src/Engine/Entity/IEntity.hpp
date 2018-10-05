
// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by Andrew Volski on 10.07.18.
//

#ifndef DEMIURGE_IENTITY_HPP
#define DEMIURGE_IENTITY_HPP

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
    IEntity(us_int id, const std::string &name);
    virtual ~IEntity() {}

    us_int id;
    std::string name;

//    sf::Vector2f Position;

public:
    IEntity() = delete;
    friend class EntityManager;

    std::vector<us_int> ComponentsId;

    virtual us_int getId()                               const noexcept final;
    virtual void setName(const std::string &name)           noexcept final;
    virtual const std::string & getName()                     const noexcept final;
    virtual void setPosition(float x, float y) = 0;
    virtual void setPosition(const sf::Vector2f &position) = 0;
    sf::Vector2f getPosition() const;

    inline bool operator==(const IEntity &rhs) const
    {
        return this->id == rhs.id;
    }

    inline bool operator!=(const IEntity &rhs) const
    {
        return this->id != rhs.id;
    }

    inline bool operator==(const IEntity *rhs) const
    {
        return this->id == rhs->id;
    }

    inline bool operator!=(const IEntity *rhs) const
    {
        return this->id != rhs->id;
    }

};

#endif //DEMIURGE_IENTITY_HPP
