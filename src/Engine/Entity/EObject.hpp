
// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by Andrew Volski on 12.07.18.
//

#ifndef DEMIURGE_EOBJECT_HPP
#define DEMIURGE_EOBJECT_HPP

#include "IEntity.hpp"

class EObject : public IEntity, public ERegisterabe<EObject>
{
protected:
    friend class ERegisterabe<EObject>;
    EObject(us_int id, const std::string &name);
    virtual ~EObject() override;

public:
    EObject() = delete;
};

#endif //DEMIURGE_EOBJECT_HPP
