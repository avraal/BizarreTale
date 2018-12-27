// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by Andrew Volski on 26.12.2018.
//

#include "CTriangle.hpp"
#include "../../Entity/EObject.hpp"
#include "../../Systems/Managers/EntityManager.hpp"
CTriangle::CTriangle(us_int id, us_int entityId, const std::string &name) : CDrawable(id, entityId, name)
{
    bodyInit(sf::PrimitiveType::Triangles, 3);
    auto parent = std::static_pointer_cast<EObject>(EntityManager::getEntity(entityId));
    setPosition(parent->getPosition());
}
void CTriangle::bodyInit(const sf::PrimitiveType &type, us_int vertexCount)
{
    body.setPrimitiveType(type);
    body.resize(vertexCount);
    bounds = ThicknessLineArray(); //ToDo: overload by class (CRectangle, CTriangle, CEllipse)
    bodyBuild();
}
void CTriangle::bodyBuild()
{
    body[0].position = {0, 0};
    body[1].position = {TDS, TDS};
    body[2].position = {0, TDS};

    setColor(color);
}