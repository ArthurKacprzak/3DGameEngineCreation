//
// Created by arthur on 10/10/2020.
//

#include "CommandPool.hpp"

CommandPool::CommandPool(Device &device, Surface &surface)
{
    QueueFamily::QueueFamilyIndices queueFamilyIndices = QueueFamily::findQueueFamilies(device.getPhysicalDevice(), surface);

    VkCommandPoolCreateInfo poolInfo{};
    poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    poolInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily.value();
    poolInfo.flags = 0; // Optionel

    if (vkCreateCommandPool(device.getDevice(), &poolInfo, nullptr, &commandPool) != VK_SUCCESS) {
        throw std::runtime_error("failed to create command pool!");
    }
}

VkCommandPool &CommandPool::getCommandPool()
{
    return commandPool;
}
