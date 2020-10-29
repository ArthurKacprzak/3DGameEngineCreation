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
    virtual void init(Window &window);

public:
    void addPoint(Vertex v);
    void setIndices(const std::vector<uint32_t> &indices);

private:
    std::vector<Vertex> vertex;
    std::vector<uint32_t> indices;
};

#endif //INC_3DGAMEENGINECREATION_OBJECT_HPP
