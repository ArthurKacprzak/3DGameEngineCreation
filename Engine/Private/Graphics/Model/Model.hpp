//
// Created by arthur on 20/10/2020.
//

#ifndef INC_3DGAMEENGINECREATION_MODEL_HPP
#define INC_3DGAMEENGINECREATION_MODEL_HPP

#include <string>
#include <vector>
#include "Vertex.hpp"

class Window;

class Model
{
public:
    Model();

public:
    static std::string getTexturePath();
    glm::mat4 model;

private:

};


#endif //INC_3DGAMEENGINECREATION_MODEL_HPP
