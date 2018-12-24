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
    bodyInit(sf::PrimitiveType::Quads, 4);
    canDraw = false;
    attachedPosition = true;
    auto parent = std::static_pointer_cast<EObject>(EntityManager::getEntity(entityId));
    setGlobalPosition(parent->getPosition());
    //    canDraw = true;
}

void CDrawable::bodyBuild()
{
    body[0].position = {0, 0};
    body[1].position = {TDS, 0};
    body[2].position = {TDS, TDS};
    body[3].position = {0, TDS};
    setColor(color);
}

void CDrawable::setColor(const sf::Color &color)
{
    this->color = color;
    body[0].color = color;
    body[1].color = color;
    body[2].color = color;
    body[3].color = color;
}

void CDrawable::setGlobalPosition(const sf::Vector2f &p)
{
    body[0].position =  p;
    body[1].position = {p.x + TDS, p.y};
    body[2].position = {p.x + TDS, p.y + TDS};
    body[3].position = {p.x, p.y + TDS};
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

    body[0].position =  startPoint;
    body[1].position = {startPoint.x + TDS, startPoint.y};
    body[2].position = {startPoint.x + TDS, startPoint.y + TDS};
    body[3].position = {startPoint.x, startPoint.y + TDS};

}

void CDrawable::bodyInit(sf::PrimitiveType type, us_int vertexCount)
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
    bounds.append({body[0].position, body[1].position});
    bounds.append({body[1].position, body[2].position});
    bounds.append({body[2].position, body[3].position});
    bounds.append({body[3].position, body[0].position});
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
