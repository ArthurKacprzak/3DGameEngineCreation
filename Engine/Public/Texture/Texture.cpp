//
// Created by arthur on 24/10/2020.
//

#include "Texture.hpp"

#include <utility>

Texture::Texture(std::string texturePath) : texturePath(std::move(texturePath))
{
}
