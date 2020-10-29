//
// Created by arthur on 21/10/2020.
//

#ifndef INC_3DGAMEENGINECREATION_OBJECT_HPP
#define INC_3DGAMEENGINECREATION_OBJECT_HPP

#include "../../Private/Window/Window.hpp"

class Object
{
public:
    Object();

public:
    virtual void init(Window &window) = 0;

public:
    virtual bool operator==(const Object &other) const = 0;
    virtual Object &operator=(const Object &rhs) = 0;
};

#endif //INC_3DGAMEENGINECREATION_OBJECT_HPP
