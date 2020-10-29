//
// Created by arthur on 21/10/2020.
//

#include "Object.hpp"

Object::Object()
{

}

void Object::init(Window &window)
{
    for (auto &i : this->vertex) {
        window.addVertice(i);
    }

    for (auto &i : this->indices) {
        window.addIndex(i);
    }
}

void Object::addPoint(Vertex v)
{
    this->vertex.push_back(v);
}

void Object::setIndices(const std::vector<uint32_t> &indices)
{
    this->indices = indices;
}
