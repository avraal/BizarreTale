
// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by Andrew Volski on 12.07.18.
//

#ifndef BIZARRETALE_EOBJECT_HPP
#define BIZARRETALE_EOBJECT_HPP

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

    std::shared_ptr<CPrimitiveQuad> body;

    virtual void setPosition(float x, float y) override;
    virtual void setPosition(const sf::Vector2f &position) override;

    virtual ~EObject();
};

#endif //BIZARRETALE_EOBJECT_HPP
