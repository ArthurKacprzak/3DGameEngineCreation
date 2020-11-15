//
// Created by arthur on 17/10/2020.
//

#ifndef INC_3DGAMEENGINECREATION_UNIFORMBUFFERS_HPP
#define INC_3DGAMEENGINECREATION_UNIFORMBUFFERS_HPP

#include <vulkan/vulkan.hpp>
#include <glm/glm.hpp>

#include "ImageViews.hpp"
#include "VertexBuffer.hpp"

class UniformBuffers
{
public:
    UniformBuffers(Device &device, ImageViews &imageViews);

    void release(Device &device, ImageViews &views);

public:
    struct UniformBufferObject {
        glm::mat4 model;
        glm::mat4 view;
        glm::mat4 proj;
        glm::vec4 lightPos = glm::vec4(0.0f, -2.0f, 0.0f, 1.0f);
        glm::vec4 cameraPos;
    };

public:
    std::vector<VkBuffer> &getUniformBuffers();
    std::vector<VkDeviceMemory> &getUniformBuffersMemory();

private:
    std::vector<VkBuffer> uniformBuffers;
    std::vector<VkDeviceMemory> uniformBuffersMemory;
};


#endif //INC_3DGAMEENGINECREATION_UNIFORMBUFFERS_HPP
