//
// Created by arthur on 20/10/2020.
//

#include "Model.hpp"

#define TINYOBJLOADER_IMPLEMENTATION
#include "../../Window/Window.hpp"
#include <iostream>

Model::Model()
{
    this->model = glm::scale(glm::mat4(1.0f), glm::vec3(0.2f));
}

std::string Model::getTexturePath()
{
    return "textures/viking_room.png";
}


