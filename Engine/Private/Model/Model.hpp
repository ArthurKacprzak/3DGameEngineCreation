//
// Created by arthur on 20/10/2020.
//

#ifndef INC_3DGAMEENGINECREATION_MODEL_HPP
#define INC_3DGAMEENGINECREATION_MODEL_HPP

#include <string>
#include <vector>
#include "../Vertex/Vertex.hpp"

class Window;

class Model
{
public:
    Model(Window *window);

public:
    static std::string getTexturePath();
    static std::string getModelPath();

private:
//    std::vector<Vertex> vertices;
//    std::vector<uint32_t> indices;
};


#endif //INC_3DGAMEENGINECREATION_MODEL_HPP
