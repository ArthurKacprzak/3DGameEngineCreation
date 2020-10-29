//
// Created by arthur on 21/10/2020.
//

#include "Rect.hpp"

Rect::Rect()
{

}

void Rect::init(Window &window)
{
    for (auto &i : this->vertex) {
        window.addVertice(i);
    }

    for (auto &i : this->indices) {
        window.addIndex(i);
    }
}

void Rect::addPoint(Vertex v)
{
    this->vertex.push_back(v);
}

void Rect::setIndices(const std::vector<uint32_t> &indices)
{
    this->indices = indices;
}
