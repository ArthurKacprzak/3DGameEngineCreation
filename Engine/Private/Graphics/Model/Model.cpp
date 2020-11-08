//
// Created by arthur on 20/10/2020.
//

#include "Model.hpp"

#define TINYOBJLOADER_IMPLEMENTATION
#include "../../Window/Window.hpp"
#include <iostream>
#include "../../../../ourLibs/miniobjloader/loader.hpp"

Model::Model(Window *window)
{
}

std::string Model::getTexturePath()
{
    return "../textures/viking_room.png";
}


