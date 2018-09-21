
// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by Andrew Volski on 12.07.18.
//

#ifndef DEMIURGE_EOBJECT_HPP
#define DEMIURGE_EOBJECT_HPP

#include "IEntity.hpp"

class CTile;
class EObject : public IEntity
{
private:
public:
    EObject();
    EObject(const EObject&);
    EObject(EObject &&eo);
    EObject&operator=(const EObject&);

    virtual void setPosition(float x, float y) override;
    virtual void setPosition(const sf::Vector2f &position) override;

    virtual ~EObject();
};

#endif //DEMIURGE_EOBJECT_HPP
