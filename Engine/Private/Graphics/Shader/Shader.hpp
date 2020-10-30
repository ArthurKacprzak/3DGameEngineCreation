//
// Created by arthur on 10/10/2020.
//

#ifndef INC_3DGAMEENGINECREATION_SHADER_HPP
#define INC_3DGAMEENGINECREATION_SHADER_HPP

#include <vulkan/vulkan.hpp>
#include <vector>
#include "../../Compute/Device/Device.hpp"

class Shader
{
public:
    static VkShaderModule createShaderModule(const std::vector<char> &code, Device &device);
};


#endif //INC_3DGAMEENGINECREATION_SHADER_HPP
