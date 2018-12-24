
// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by Andrew Volski on 12.07.18.
//

#include "EObject.hpp"
#include "../Systems/Managers/ComponentManager.hpp"

EObject::~EObject()
{
}
EObject::EObject(us_int id, const std::string &name) : IEntity(id, name)
{
}
void EObject::setPosition(const sf::Vector2f &pos)
{
    auto n_pos = pos - transform->getPosition();
    transform->setPosition(pos);

    for (auto i : ComponentsId)
    {
        auto d = std::dynamic_pointer_cast<CDrawable>(ComponentManager::getComponent(i));
        if (d)
        {
            if (d->isAttachedPosition())
            {
                d->setLocalePosition(n_pos);
            }
        }
    }

}
void EObject::setPosition(const sf::Vector2i &pos)
{
    setPosition(sf::Vector2f(pos));
}
const sf::Vector2f &EObject::getPosition()
{
    return transform->getPosition();
}
void EObject::init()
{
    transform = ComponentManager::Create<CTransform>(id, "transform");
}
void EObject::move(const sf::Vector2f &offset)
{
    setPosition(getPosition() + offset);
}
