//
// Created by arthur on 10/10/2020.
//

#include "ImageViews.hpp"

ImageViews::ImageViews()
{

}

void ImageViews::setSwapChainImageFormat(VkFormat format)
{
    this->swapChainImageFormat = format;
}

void ImageViews::setSwapChainExtent(const VkExtent2D &extent)
{
    this->swapChainExtent = extent;
}

void ImageViews::swapChainImagesResize(uint32_t imageCount)
{
    this->swapChainImages.resize(imageCount);
}

std::vector<VkImage> &ImageViews::getSwapChainImages()
{
    return this->swapChainImages;
}

void ImageViews::init(Device &device)
{
    this->swapChainImageViews.resize(this->swapChainImages.size());

    for (size_t i = 0; i < this->swapChainImages.size(); i++) {
        VkImageViewCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        createInfo.image = this->swapChainImages[i];
        createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
        createInfo.format = this->swapChainImageFormat;
        createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        createInfo.subresourceRange.baseMipLevel = 0;
        createInfo.subresourceRange.levelCount = 1;
        createInfo.subresourceRange.baseArrayLayer = 0;
        createInfo.subresourceRange.layerCount = 1;

        if (vkCreateImageView(device.getDevice(), &createInfo, nullptr, &swapChainImageViews[i]) != VK_SUCCESS) {
            throw std::runtime_error("failed to create image views!");
        }
    }
}

VkExtent2D &ImageViews::getSwapChainExtent()
{
    return swapChainExtent;
}

VkFormat &ImageViews::getSwapChainImageFormat()
{
    return swapChainImageFormat;
}

std::vector<VkImageView> &ImageViews::getSwapChainImageViews()
{
    return swapChainImageViews;
}
