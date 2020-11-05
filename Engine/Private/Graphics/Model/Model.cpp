//
// Created by arthur on 20/10/2020.
//

#include "Model.hpp"

#define TINYOBJLOADER_IMPLEMENTATION
#include "../../Window/Window.hpp"
#include <iostream>
#include "../../../../ourLibs/miniobjloader/loader.hpp"
#include "../../Tools/VkTools.hpp"

Model::Model(Window *window, Device &device, CommandPool &commandPool)
{
    miniobj::loader loader;
    miniobj::attrib_t attribM;
    std::vector<miniobj::shape_t> shapesM;
    loader.load(&attribM, &shapesM, Model::getModelPath());

    std::unordered_map<Vertex, uint32_t> uniqueVertices{};

    for (const auto& shape : shapesM) {
        for (const auto& index : shape.mesh.indices) {
            Vertex vertex{};

            vertex.pos = {
                    attribM.vertices[3 * index.vertex_index + 0],
                    attribM.vertices[3 * index.vertex_index + 1],
                    attribM.vertices[3 * index.vertex_index + 2]
            };

            vertex.texCoord = {
                    attribM.texcoords[2 * index.texcoord_index + 0],
                    1.0f - attribM.texcoords[2 * index.texcoord_index + 1]
            };

            vertex.color = {1.0f, 1.0f, 1.0f};

            if (uniqueVertices.count(vertex) == 0) {
                uniqueVertices[vertex] = static_cast<uint32_t>(window->getVertices().size());
                window->addVertice(vertex);
            }

            window->addIndex(uniqueVertices[vertex]);
        }
    }

    this->createBuffer(device, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, sizeof(glm::mat4));

    vkMapMemory(device.getDevice(), memory, 0, size, 0, &this->mapped);
}

std::string Model::getTexturePath()
{
    return "textures/viking_room.png";
}

std::string Model::getModelPath()
{
    return "Resources/viking_room.obj";
}

VkDescriptorBufferInfo &Model::getDescriptor()
{
    return descriptor;
}

VkResult Model::createBuffer(Device &device, VkBufferUsageFlags usageFlags, VkMemoryPropertyFlags memoryPropertyFlags, VkDeviceSize size)
{
    VkBufferCreateInfo bufferCreateInfo = this->bufferCreateInfo(usageFlags, size);
    VK_CHECK_RESULT(vkCreateBuffer(device.getDevice(), &bufferCreateInfo, nullptr, &this->buffer));

    VkMemoryRequirements memReqs;

    VkMemoryAllocateInfo memAlloc {};
    memAlloc.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;

    vkGetBufferMemoryRequirements(device.getDevice(), this->buffer, &memReqs);
    memAlloc.allocationSize = memReqs.size;
    memAlloc.memoryTypeIndex = device.getMemoryType(memReqs.memoryTypeBits, memoryPropertyFlags);
    // If the buffer has VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT set we also need to enable the appropriate flag during allocation
    VkMemoryAllocateFlagsInfoKHR allocFlagsInfo{};
    if (usageFlags & VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT) {
        allocFlagsInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO_KHR;
        allocFlagsInfo.flags = VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT_KHR;
        memAlloc.pNext = &allocFlagsInfo;
    }
    VK_CHECK_RESULT(vkAllocateMemory(device.getDevice(), &memAlloc, nullptr, &this->memory));

    this->alignment = memReqs.alignment;
    this->size = size;
    this->usageFlags = usageFlags;
    this->memoryPropertyFlags = memoryPropertyFlags;

    descriptor.offset = 0;
    descriptor.buffer = buffer;
    descriptor.range = VK_WHOLE_SIZE;

    // Attach the memory to the buffer object
    return vkBindBufferMemory(device.getDevice(), buffer, memory, 0);
}

VkBufferCreateInfo Model::bufferCreateInfo(VkBufferUsageFlags usage, VkDeviceSize size)
{
    VkBufferCreateInfo bufCreateInfo {};
    bufCreateInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufCreateInfo.usage = usage;
    bufCreateInfo.size = size;
    return bufCreateInfo;
}

void Model::setModelMat(glm::mat4 mat)
{
    this->modelMat = mat;
}

glm::mat4 &Model::getModelMat()
{
    return modelMat;
}

glm::vec3 &Model::getRotation()
{
    return rotation;
}

void *Model::getMapped()
{
    return mapped;
}

