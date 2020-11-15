//
// Created by arthur on 19/10/2020.
//

#ifndef INC_3DGAMEENGINECREATION_TEXTURESAMPLER_HPP
#define INC_3DGAMEENGINECREATION_TEXTURESAMPLER_HPP

#include "Device.hpp"

class TextureSampler
{
public:
    TextureSampler(Device &device);

    void release(Device &device);

public:
    VkSampler &getTextureSampler();

private:
    VkSampler textureSampler;
};


#endif //INC_3DGAMEENGINECREATION_TEXTURESAMPLER_HPP
