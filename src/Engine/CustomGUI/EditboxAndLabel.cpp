
// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by Andrew Volski on 07.08.18.
//

#include "EditboxAndLabel.hpp"
namespace tgui
{
    void EditboxAndLabel::setPosition(const Layout2d &position)
    {
        label->setPosition(position);
        Widget::setPosition({label->getSize().x + 4, position.y});
    }
    void EditboxAndLabel::draw(sf::RenderTarget &target, sf::RenderStates states) const
    {
        EditBox::draw(target, states);
        label->draw(target, states);
    }
    EditboxAndLabel::EditboxAndLabel(const sf::String &labelText)
    {
        m_type = "EditboxAndLabel";
        label = Label::create(labelText);
    }
    EditboxAndLabel::Ptr EditboxAndLabel::create(const sf::String &labelText)
    {
        return std::make_shared<EditboxAndLabel>(labelText);
    }
    EditboxAndLabel::Ptr EditboxAndLabel::copy(EditboxAndLabel::ConstPtr editBox)
    {
        if (editBox)
        {
            return std::static_pointer_cast<EditboxAndLabel>(editBox->clone());
        } else
        {
            return nullptr;
        }
    }
    sf::Vector2f EditboxAndLabel::getPosition() const
    {
        return label->getPosition();
    }
}