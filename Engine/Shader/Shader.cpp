//
// Created by arthur on 10/10/2020.
//

#include "Shader.hpp"

VkShaderModule Shader::createShaderModule(const std::vector<char> &code, Device &device)
{
    VkShaderModuleCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    createInfo.codeSize = code.size();
    createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());

    VkShaderModule shaderModule;
    if (vkCreateShaderModule(device.getDevice(), &createInfo, nullptr, &shaderModule) != VK_SUCCESS) {
        throw std::runtime_error("échec de la création d'un module shader!");
    }
    return shaderModule;
}
