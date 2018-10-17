
// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by Andrew Volski on 10.07.18.
//

#ifndef DEMIURGE_IENTITY_HPP
#define DEMIURGE_IENTITY_HPP

#include <vector>
#include <memory>
#include <algorithm>
#include "../CONST_DEFINITIONS.hpp"

class IEntity;

template <typename T>
class ERegisterabe
{
protected:
    friend class EntityManager;
    static IEntity *Create(us_int id, const std::string &name)
    {
        return new T(id, name);
    }
};

class IEntity
{
private:
    friend class EntityManager;
protected:
    IEntity(us_int id, const std::string &name);
    virtual ~IEntity() = 0;

    us_int id;
    std::string name;

public:
    IEntity() = delete;

    std::vector<us_int> ComponentsId;

    us_int getId() const;
    void setName(const std::string &name);
    const std::string &getName() const;
};

#endif //DEMIURGE_IENTITY_HPP
