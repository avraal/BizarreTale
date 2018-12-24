
// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by Andrew Volski on 12.07.18.
//

#ifndef DEMIURGE_EOBJECT_HPP
#define DEMIURGE_EOBJECT_HPP

#include "IEntity.hpp"
#include "../Components/CDrawable.hpp"
#include "../Components/CTransform.hpp"

class EObject : public IEntity, public ERegisterable<EObject>
{
    //TODO: Make this protected
public:
    friend class ERegisterable<EObject>;
    EObject(us_int id, const std::string &name);
public:
    virtual ~EObject();
    std::shared_ptr<CTransform> transform;
    EObject() = delete;
    void setPosition(const sf::Vector2f &pos);
    void setPosition(const sf::Vector2i &pos);
    void move(const sf::Vector2f &offset);
    virtual void init() override;
    const sf::Vector2f &getPosition();
};

#endif //DEMIURGE_EOBJECT_HPP