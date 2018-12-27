// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by Andrew Volski on 26.12.2018.
//

#ifndef DEMIURGE_CTRIANGLE_HPP
#define DEMIURGE_CTRIANGLE_HPP

#include "../CDrawable.hpp"

class CTriangle : public CDrawable, public CRegisterable<CTriangle>
{
public:
    using CRegisterable<CTriangle>::Create;
    CTriangle(us_int id, us_int entityId, const std::string &name);
public:
    virtual void bodyInit(const sf::PrimitiveType &type, us_int vertexCount) override;
    virtual void bodyBuild() override;
    virtual ~CTriangle() {}
};

#endif //DEMIURGE_CTRIANGLE_HPP
