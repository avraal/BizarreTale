
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
    virtual ~EObject();
public:
    std::shared_ptr<CDrawable> body;
    std::shared_ptr<CTransform> transform;
    EObject() = delete;
    //    CDrawable *getBody() const;
    //    CTransform *getTransform() const;
    void setPosition(const sf::Vector2f &pos);
    void setPosition(const sf::Vector2i &pos);
};

#endif //DEMIURGE_EOBJECT_HPP