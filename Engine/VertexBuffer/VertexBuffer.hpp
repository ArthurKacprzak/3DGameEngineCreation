//
// Created by arthur on 16/10/2020.
//

#ifndef INC_3DGAMEENGINECREATION_VERTEXBUFFER_HPP
#define INC_3DGAMEENGINECREATION_VERTEXBUFFER_HPP

#include <vulkan/vulkan.hpp>

#include "../Device/Device.hpp"
#include "../Vertex/Vertex.hpp"
#include "../CommandPool/CommandPool.hpp"

class VertexBuffer
{
public:
    VertexBuffer(Device &device, CommandPool &commandPool, std::vector<Vertex> &vertices);

public:
    static void createBuffer(Device &device, VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer &buffer, VkDeviceMemory &bufferMemory);
    static uint32_t findMemoryType(Device &device, uint32_t typeFilter, VkMemoryPropertyFlags properties);

private:
    void copyBuffer(Device &device, CommandPool &commandPool, VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

public:
    VkBuffer &getIndexBuffer();

    std::vector<uint16_t> &getIndices();

private:
    void createIndexBuffer(Device &device, CommandPool &commandPool);

private:
    VkBuffer vertexBuffer;
    VkDeviceMemory vertexBufferMemory;
    VkBuffer indexBuffer;
    VkDeviceMemory indexBufferMemory;

    std::vector<uint16_t> indices = {
            0, 1, 2, 2, 3, 0
    };

public:
    VkDeviceMemory &getVertexBufferMemory();
    VkBuffer &getVertexBuffer();
};


#endif //INC_3DGAMEENGINECREATION_VERTEXBUFFER_HPP
