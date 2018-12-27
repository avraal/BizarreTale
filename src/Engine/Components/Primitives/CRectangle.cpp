// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by Andrew Volski on 25.12.2018.
//

#include "CRectangle.hpp"
#include "../../Entity/EObject.hpp"
#include "../../Systems/Managers/EntityManager.hpp"
CRectangle::CRectangle(us_int id, us_int entityId, const std::string &name) : CDrawable(id, entityId, name)
{
    bodyInit(sf::PrimitiveType::Quads, 4);
    auto parent = std::static_pointer_cast<EObject>(EntityManager::getEntity(entityId));
    setPosition(parent->getPosition());
}
void CRectangle::bodyBuild()
{
    body[0].position = {0, 0};
    body[1].position = {TDS, 0};
    body[2].position = {TDS, TDS};
    body[3].position = {0, TDS};
    setColor(color);
}

void CRectangle::bodyInit(const sf::PrimitiveType &type, us_int vertexCount)
{
    body.setPrimitiveType(type);
    body.resize(vertexCount);
    bounds = ThicknessLineArray(); //ToDo: overload by class (CRectangle, CTriangle, CEllipse)
    bodyBuild();
}