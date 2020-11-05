//
// Created by arthur on 16/10/2020.
//

#ifndef INC_3DGAMEENGINECREATION_VERTEXBUFFER_HPP
#define INC_3DGAMEENGINECREATION_VERTEXBUFFER_HPP

#include <vulkan/vulkan.hpp>

#include "../../Compute/Device/Device.hpp"
#include "../Vertex/Vertex.hpp"
#include "../../Compute/CommandPool/CommandPool.hpp"

class Window;

class VertexBuffer
{
public:
    VertexBuffer(Device &device, CommandPool &commandPool, std::vector<Vertex> &vertices, std::vector<uint32_t> indices);

public:
    static void createBuffer(Device &device, VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer &buffer, VkDeviceMemory &bufferMemory);
    static uint32_t findMemoryType(Device &device, uint32_t typeFilter, VkMemoryPropertyFlags properties);

private:
    void copyBuffer(Device &device, CommandPool &commandPool, VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

private:
    void createIndexBuffer(std::vector<uint32_t> &indices, Device &device, CommandPool &commandPool);

private:
    VkBuffer vertexBuffer;
    VkDeviceMemory vertexBufferMemory;
    VkBuffer indexBuffer;
    VkDeviceMemory indexBufferMemory;

public:
    VkDeviceMemory &getVertexBufferMemory();
    VkBuffer &getVertexBuffer();
    VkBuffer &getIndexBuffer();
    VkDeviceMemory &getIndexBufferMemory();
};


#endif //INC_3DGAMEENGINECREATION_VERTEXBUFFER_HPP
