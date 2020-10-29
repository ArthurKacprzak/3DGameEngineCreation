//
// Created by arthur on 21/10/2020.
//

#ifndef INC_3DGAMEENGINECREATION_RECT_HPP
#define INC_3DGAMEENGINECREATION_RECT_HPP

#include "../Object/Object.hpp"
#include "../../Private/Vertex/Vertex.hpp"
#include <list>

class Rect : public Object
{
public:
    Rect();

private:
    void init(Window &window) override;

public:
    void addPoint(Vertex v);
    void setIndices(const std::vector<uint32_t> &indices);

public:
    bool operator==(const Object &other) const override {
        return this->vertex == dynamic_cast<const Rect &>(other).vertex;
    }

    Object &operator=(const Object& rhs) override
    {
        return *this;
    }

private:
    std::vector<Vertex> vertex;
    std::vector<uint32_t> indices;
};


#endif //INC_3DGAMEENGINECREATION_RECT_HPP
