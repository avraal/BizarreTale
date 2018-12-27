// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by Andrew Volski on 25.12.2018.
//

#ifndef DEMIURGE_CRECTANGLE_HPP
#define DEMIURGE_CRECTANGLE_HPP

#include "../CDrawable.hpp"

class CRectangle : public CDrawable, public CRegisterable<CRectangle>
{
public:
    using CRegisterable<CRectangle>::Create;
    CRectangle(us_int id, us_int entityId, const std::string &name);
    virtual void bodyBuild() override;
    virtual void bodyInit(const sf::PrimitiveType &type, us_int vertexCount) override;
public:
    virtual ~CRectangle() {}
};

#endif //DEMIURGE_CRECTANGLE_HPP
