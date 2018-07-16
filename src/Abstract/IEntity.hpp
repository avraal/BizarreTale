
// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by Andrew Volski on 10.07.18.
//

#ifndef BIZARRETALE_IENTITY_HPP
#define BIZARRETALE_IENTITY_HPP

#include <vector>
#include <memory>
#include "../PrimitiveQuad.hpp"

class IComponent;
class IEntity
{
protected:
    int Id;
    std::vector<std::shared_ptr<IComponent>> Components;
public:
    int GetId();
    void setId(int id);
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

    std::vector<std::shared_ptr<PrimitiveQuad>> getDrawable()
    {
        std::vector<std::shared_ptr<PrimitiveQuad>> result;
        for(auto &c : Components)
        {
//            PrimitiveQuad *p = dynamic_cast<PrimitiveQuad*>(c.get());
            std::shared_ptr<PrimitiveQuad> p1 = std::dynamic_pointer_cast<PrimitiveQuad>(c);
            if(p1)
            {
                result.push_back(p1);
            }
        }
        std::cout << "Add p1" << std::endl;
        return result;
    }

    virtual ~IEntity() = 0;
};

#endif //BIZARRETALE_IENTITY_HPP
