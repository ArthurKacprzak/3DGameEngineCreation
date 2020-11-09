//
// Created by arthur on 19/10/2020.
//

#include "TextureImageView.hpp"

TextureImageView::TextureImageView(Device &device, TextureImage &textureImage)
{
    textureImageView = createImageView(device, textureImage.getTextureImage(), VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_ASPECT_COLOR_BIT);
}

VkImageView TextureImageView::createImageView(Device &device, VkImage &image, VkFormat format, VkImageAspectFlags aspectFlags) {
    VkImageViewCreateInfo viewInfo{};
    viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    viewInfo.image = image;
    viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
    viewInfo.format = format;
    viewInfo.subresourceRange.aspectMask = aspectFlags;
    viewInfo.subresourceRange.baseMipLevel = 0;
    viewInfo.subresourceRange.levelCount = 1;
    viewInfo.subresourceRange.baseArrayLayer = 0;
    viewInfo.subresourceRange.layerCount = 1;

    VkImageView imageView;
    if (vkCreateImageView(device.getDevice(), &viewInfo, nullptr, &imageView) != VK_SUCCESS) {
        throw std::runtime_error("failed to create texture image view!");
    }

    return imageView;
}

VkImageView &TextureImageView::getTextureImageView()
{
    return textureImageView;
}

void TextureImageView::release(Device &device)
{
    vkDestroyImageView(device.getDevice(), this->textureImageView, nullptr);
}
