
// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by Andrew Volski on 10.07.18.
//

#ifndef BIZARRETALE_IENTITY_HPP
#define BIZARRETALE_IENTITY_HPP

#include <vector>
#include <memory>
#include "../CPrimitiveQuad.hpp"

class Level;
class IComponent;
class CTile;
class IEntity
{
protected:
    int Id;
    sf::Vector2f Position;
    std::string Name;
    std::vector<IComponent*> Components;
    CPrimitiveQuad *body;
public:
    IEntity(int id = -1);

    virtual int GetId()                               const noexcept final;
    virtual void setId(int id)                              noexcept final;
    virtual void setName(const std::string &name)           noexcept final;
    void setPosition(float x, float y);
    void setPosition(const sf::Vector2f &position);
    sf::Vector2f getPosition()                        const;
    CPrimitiveQuad *getBody();
    virtual std::string getName()                     const noexcept final;
    void addComponent(IComponent *component);
    template <class T>
    T *getComponent()
    {
        for(auto c : Components)
        {
            T *t = dynamic_cast<T*>(c);
            if(t != nullptr)
            {
                return t;
            }
        }
        return nullptr;
    }
    template <class T>
    T *getComponentByName(const std::string &name)
    {
        for(auto c : Components)
        {
            if(c->getName() == name)
            {
                T *t = dynamic_cast<T*>(c);
                if(t != nullptr)
                {
                    return t;
                }
            }
        }
        return nullptr;
    }

    std::vector<CPrimitiveQuad*> getDrawable()
    {
        std::vector<CPrimitiveQuad*> result;
        for(auto &c : Components)
        {
            CPrimitiveQuad *p1 = dynamic_cast<CPrimitiveQuad*>(c);
            if(p1 != nullptr)
            {
                result.push_back(p1);
                std::cout << "Add component to " << getName() << std::endl;
            }
        }
        return result;
    }

    virtual ~IEntity() = 0;
};

#endif //BIZARRETALE_IENTITY_HPP
