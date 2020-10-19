//
// Created by arthur on 17/10/2020.
//

#ifndef INC_3DGAMEENGINECREATION_UNIFORMBUFFERS_HPP
#define INC_3DGAMEENGINECREATION_UNIFORMBUFFERS_HPP

#include <vulkan/vulkan.hpp>
#include <glm/glm.hpp>

#include "../ImageViews/ImageViews.hpp"
#include "../VertexBuffer/VertexBuffer.hpp"

class UniformBuffers
{
public:
    UniformBuffers(Device &device, ImageViews &imageViews);

public:
    struct UniformBufferObject {
        alignas(16) glm::mat4 model;
        alignas(16) glm::mat4 view;
        alignas(16) glm::mat4 proj;
    };

public:
    std::vector<VkBuffer> &getUniformBuffers();
    std::vector<VkDeviceMemory> &getUniformBuffersMemory();

private:
    std::vector<VkBuffer> uniformBuffers;
    std::vector<VkDeviceMemory> uniformBuffersMemory;
};


#endif //INC_3DGAMEENGINECREATION_UNIFORMBUFFERS_HPP
