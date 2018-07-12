
// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by Andrew Volski on 10.07.18.
//

#ifndef BIZARRETALE_IENTITY_HPP
#define BIZARRETALE_IENTITY_HPP

#include <vector>
#include <memory>

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

    virtual ~IEntity() = 0;
};

#endif //BIZARRETALE_IENTITY_HPP
