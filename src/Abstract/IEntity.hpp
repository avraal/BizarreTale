
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
    std::vector<std::shared_ptr<IComponent>> Components;
    std::shared_ptr<CPrimitiveQuad> body;
public:
    IEntity(int id = -1);

    int GetId() const;
    void setId(int id);
    void setName(const std::string &name);
    void setPosition(float x, float y);
    void setPosition(const sf::Vector2f &position);
    sf::Vector2f getPosition() const;
    std::shared_ptr<CPrimitiveQuad> getBody();
    std::string getName() const;
    void addComponent(std::shared_ptr<IComponent> component);
    template <class T>
    T *getComponent()
    {
        for(auto c : Components)
        {
            T *t = dynamic_cast<T*>(c.get());
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
                T *t = dynamic_cast<T*>(c.get());
                if(t != nullptr)
                {
                    return t;
                }
            }
        }
        return nullptr;
    }

    std::vector<std::shared_ptr<CPrimitiveQuad>> getDrawable()
    {
        std::vector<std::shared_ptr<CPrimitiveQuad>> result;
        for(auto &c : Components)
        {
            std::shared_ptr<CPrimitiveQuad> p1 = std::dynamic_pointer_cast<CPrimitiveQuad>(c);
            if(p1)
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
