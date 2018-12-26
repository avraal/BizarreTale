// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by Andrew Volski on 08.10.18.
//

#include <SFML/Graphics/RectangleShape.hpp>
#include "CDrawable.hpp"
#include "../Systems/Managers/EntityManager.hpp"
#include "../Entity/EObject.hpp"
CDrawable::CDrawable(us_int id, us_int entityId, const std::string &name, const std::string &ImagePath, sf::Color c,
                     us_int index) : IComponent(id, entityId, name)
{
    this->color = c;
    this->index = index;
    this->ImagePath = ImagePath;
    showBounds = false;
    canDraw = false;
    attachedPosition = true;
    //    canDraw = true;
}

void CDrawable::setColor(const sf::Color &color)
{
    this->color = color;
    for (int i = 0; i < body.getVertexCount(); i++)
    {
        body[i].color = color;
    }
}

void CDrawable::setGlobalPosition(const sf::Vector2f &p)
{
    setPosition(p);
}

void CDrawable::setLocalePosition(const sf::Vector2f &p)
{
    auto parent = std::static_pointer_cast<EObject>(EntityManager::getEntity(entityId));
    sf::Vector2f startPoint;
    //    if (attachedPosition)
    //    {
    //        startPoint = body[0].position + p;
    //    } else
    //    {
    //        startPoint = parent->getPosition() + p;
    //    }
    //    startPoint = body[0].position + p;
    startPoint = body[0].position + p;
    setPosition(startPoint);
}

void CDrawable::bodyInit(const sf::PrimitiveType &type, us_int vertexCount)
{
    body.setPrimitiveType(type);
    body.resize(vertexCount);
    bounds = ThicknessLineArray();
    bodyBuild();
}
const sf::Color &CDrawable::getColor() const
{
    return color;
}
us_int CDrawable::getIndex() const
{
    return index;
}
const std::string &CDrawable::getImagePath() const
{
    return ImagePath;
}
void CDrawable::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    if (canDraw)
    {
        target.draw(body, states);
        target.draw(bounds, states);
    }
}
const sf::Texture &CDrawable::getTexture() const
{
    return texture;
}
void CDrawable::drawBounds()
{
    bounds.clear();
    for (int i = 0; i < body.getVertexCount(); i++)
    {
        bounds.append({body[i].position, body[i == (body.getVertexCount() - 1) ? 0 : i+1].position});
    }
}
bool CDrawable::isShowBounds() const
{
    return showBounds;
}
void CDrawable::setShowBounds(bool showBounds)
{
    this->showBounds = showBounds;
}
void CDrawable::hideBounds()
{
    bounds.clear();
    showBounds = false;
}
void CDrawable::setIndex(us_int index)
{
    this->index = index;
}
const sf::VertexArray &CDrawable::getBody() const
{
    return body;
}
bool CDrawable::isCanDraw() const
{
    return canDraw;
}
void CDrawable::setCanDraw(bool isDraw)
{
    this->canDraw = isDraw;
}
bool CDrawable::isAttachedPosition() const
{
    return attachedPosition;
}
void CDrawable::setIsAttachedPosition(bool isAttachedPosition)
{
    this->attachedPosition = isAttachedPosition;
}
void CDrawable::rotate(float angle)
{
//    float rotate = static_cast<float>(std::fmod(angle, 360));
//    if (rotate < 0)
//    {
//        rotate += 360.f;
//    }
    sf::Vector2f rotatedPoint;
    rotatedPoint.x = body[0].position.x * std::cos(angle) - body[0].position.y * std::sin(angle);
    rotatedPoint.y = body[0].position.x * std::sin(angle) + body[0].position.y * std::cos(angle);

    setPosition(rotatedPoint);
}

