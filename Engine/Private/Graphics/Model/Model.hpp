//
// Created by arthur on 20/10/2020.
//

#ifndef INC_3DGAMEENGINECREATION_MODEL_HPP
#define INC_3DGAMEENGINECREATION_MODEL_HPP

#include <string>
#include <vector>
#include "../Vertex/Vertex.hpp"
#include "../VertexBuffer/VertexBuffer.hpp"

class Window;

class Model
{
public:
    Model(Window *window, Device &device, CommandPool &commandPool);

public:
    static std::string getTexturePath();
    static std::string getModelPath();

    VkDescriptorBufferInfo &getDescriptor();
    void setModelMat(glm::mat4);

    glm::mat4 &getModelMat();

    glm::vec3 &getRotation();

    void *getMapped();

private:
    VkDescriptorBufferInfo descriptor;
    VkBuffer buffer = VK_NULL_HANDLE;
    VkDeviceMemory memory = VK_NULL_HANDLE;
    VkDeviceSize size = 0;
    VkDeviceSize alignment = 0;
    VkBufferUsageFlags usageFlags;
    VkMemoryPropertyFlags memoryPropertyFlags;
    void* mapped = nullptr;

    glm::mat4 modelMat;
    glm::vec3 rotation;

    VkResult createBuffer(Device &device, VkBufferUsageFlags usageFlags, VkMemoryPropertyFlags memoryPropertyFlags, VkDeviceSize size);
    VkBufferCreateInfo bufferCreateInfo(VkBufferUsageFlags usage, VkDeviceSize size);
};


#endif //INC_3DGAMEENGINECREATION_MODEL_HPP
