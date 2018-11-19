// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by Andrew Volski on 08.10.18.
//

#ifndef DEMIURGE_CTRANSFORM_HPP
#define DEMIURGE_CTRANSFORM_HPP

#include <SFML/Graphics/Transformable.hpp>
#include "IComponent.hpp"

class CTransform :public IComponent, public CRegisterable<CTransform>, public sf::Transformable
{
public:
    CTransform(us_int id, us_int entityId, const std::string &name, const sf::Vector2f &pos = {0, 0});
    virtual ~CTransform() {}
    friend class CRegisterable<CTransform>;

public:
    CTransform() = delete;
};

#endif //DEMIURGE_CTRANSFORM_HPP