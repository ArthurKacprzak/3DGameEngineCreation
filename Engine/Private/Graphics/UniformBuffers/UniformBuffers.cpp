//
// Created by arthur on 17/10/2020.
//

#include "UniformBuffers.hpp"

UniformBuffers::UniformBuffers(Device &device, ImageViews &imageViews)
{
    VkDeviceSize bufferSize = sizeof(UniformBuffers::UniformBufferObject);

    this->uniformBuffers.resize(imageViews.getSwapChainImages().size());
    this->uniformBuffersMemory.resize(imageViews.getSwapChainImages().size());

    for (size_t i = 0; i < imageViews.getSwapChainImages().size(); i++) {
        VertexBuffer::createBuffer(device, bufferSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
                                   VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, uniformBuffers[i], uniformBuffersMemory[i]);
    }
}

std::vector<VkBuffer> &UniformBuffers::getUniformBuffers()
{
    return uniformBuffers;
}

std::vector<VkDeviceMemory> &UniformBuffers::getUniformBuffersMemory()
{
    return uniformBuffersMemory;
}

void UniformBuffers::release(Device &device, ImageViews &views)
{
    for (size_t i = 0; i < views.getSwapChainImages().size(); i++) {
        vkDestroyBuffer(device.getDevice(), uniformBuffers[i], nullptr);
        vkFreeMemory(device.getDevice(), uniformBuffersMemory[i], nullptr);
    }
}
