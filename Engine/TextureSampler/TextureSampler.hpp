//
// Created by arthur on 19/10/2020.
//

#ifndef INC_3DGAMEENGINECREATION_TEXTURESAMPLER_HPP
#define INC_3DGAMEENGINECREATION_TEXTURESAMPLER_HPP

#include "../Device/Device.hpp"

class TextureSampler
{
public:
    TextureSampler(Device &device);

public:
    VkSampler &getTextureSampler();

private:
    VkSampler textureSampler;
};


#endif //INC_3DGAMEENGINECREATION_TEXTURESAMPLER_HPP
