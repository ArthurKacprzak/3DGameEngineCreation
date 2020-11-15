//
// Created by arthur on 17/10/2020.
//

#ifndef INC_3DGAMEENGINECREATION_UNIFORMBUFFERS_HPP
#define INC_3DGAMEENGINECREATION_UNIFORMBUFFERS_HPP

#include <vulkan/vulkan.hpp>

#include "Math.hpp"
#include "ImageViews.hpp"
#include "VertexBuffer.hpp"

class UniformBuffers
{
public:
    UniformBuffers(Device &device, ImageViews &imageViews);

    void release(Device &device, ImageViews &views);

public:
    struct UniformBufferObject {
        struct mat4 model;
        struct mat4 view;
        struct mat4 proj;
        struct vec4 lightPos = Math::vec4(0.0f, -2.0f, 0.0f, 1.0f);
        struct vec4 cameraPos;
    };

public:
    std::vector<VkBuffer> &getUniformBuffers();
    std::vector<VkDeviceMemory> &getUniformBuffersMemory();

private:
    std::vector<VkBuffer> uniformBuffers;
    std::vector<VkDeviceMemory> uniformBuffersMemory;
};


#endif //INC_3DGAMEENGINECREATION_UNIFORMBUFFERS_HPP
