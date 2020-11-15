//
// Created by arthur on 20/10/2020.
//

#include <iostream>

#include "Model.hpp"


Model::Model()
{
    this->model = Math::scaleMat(Math::mat4(1.0f), Math::vec3(0.2f));
}

std::string Model::getTexturePath()
{
    return "textures/viking_room.png";
}


