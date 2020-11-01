//
// Created by arthur on 17/10/2020.
//

#include "DescriptorPool.hpp"
#include <array>

DescriptorPool::DescriptorPool(Device &device, ImageViews &imageViews)
{
    std::array<VkDescriptorPoolSize, 2> poolSizes{};
    poolSizes[0].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    poolSizes[0].descriptorCount = static_cast<uint32_t>(imageViews.getSwapChainImages().size());
    poolSizes[1].type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    poolSizes[1].descriptorCount = static_cast<uint32_t>(imageViews.getSwapChainImages().size());

    VkDescriptorPoolCreateInfo poolInfo{};
    poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    poolInfo.poolSizeCount = static_cast<uint32_t>(poolSizes.size());
    poolInfo.pPoolSizes = poolSizes.data();
    poolInfo.maxSets = static_cast<uint32_t>(imageViews.getSwapChainImages().size());

    if (vkCreateDescriptorPool(device.getDevice(), &poolInfo, nullptr, &descriptorPool) != VK_SUCCESS) {
        throw std::runtime_error("failed to create descriptor pool!");
    }
}

VkDescriptorPool &DescriptorPool::getDescriptorPool()
{
    return this->descriptorPool;
}

void DescriptorPool::release(Device &device)
{
    vkDestroyDescriptorPool(device.getDevice(), descriptorPool, nullptr);
}
