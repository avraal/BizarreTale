
// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by Andrew Volski on 07.08.18.
//

#ifndef DEMIURGE_EDITBOXANDLABEL_HPP
#define DEMIURGE_EDITBOXANDLABEL_HPP

#include <TGUI/Widgets/EditBox.hpp>
#include <TGUI/Widgets/Label.hpp>

namespace tgui
{

    class EditboxAndLabel : public EditBox
    {
    public:
        EditboxAndLabel() = delete;
        EditboxAndLabel(const sf::String &);

        typedef std::shared_ptr<EditboxAndLabel> Ptr;

        typedef std::shared_ptr<const EditboxAndLabel> ConstPtr;

        static EditboxAndLabel::Ptr create(const sf::String &);
        static EditboxAndLabel::Ptr copy(EditboxAndLabel::ConstPtr editBox);

        Label::Ptr label;

        Widget::Ptr clone() const override
        {
            return std::make_shared<EditboxAndLabel>(*this);
        }

        virtual void setPosition(const Layout2d &position) override;
        virtual sf::Vector2f getPosition() const;
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
        virtual ~EditboxAndLabel()
        {
        }
    };
}
#endif //DEMIURGE_EDITBOXANDLABEL_HPP
