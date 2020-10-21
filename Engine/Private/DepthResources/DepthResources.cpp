//
// Created by arthur on 19/10/2020.
//

#include "DepthResources.hpp"

DepthResources::DepthResources(Device &device, ImageViews &imageViews)
{
    VkFormat depthFormat = DepthResources::findDepthFormat(device);

    TextureImage::createImage(device, imageViews.getSwapChainExtent().width, imageViews.getSwapChainExtent().height, depthFormat, VK_IMAGE_TILING_OPTIMAL,
                VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, depthImage,
                depthImageMemory);
    depthImageView = TextureImageView::createImageView(device, depthImage, depthFormat, VK_IMAGE_ASPECT_DEPTH_BIT);
}

VkFormat DepthResources::findDepthFormat(Device &device)
{
    return DepthResources::findSupportedFormat(
            device,
            {VK_FORMAT_D32_SFLOAT, VK_FORMAT_D32_SFLOAT_S8_UINT, VK_FORMAT_D24_UNORM_S8_UINT},
            VK_IMAGE_TILING_OPTIMAL,
            VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT
    );
}

VkFormat DepthResources::findSupportedFormat(Device &device, const std::vector<VkFormat> &candidates, VkImageTiling tiling, VkFormatFeatureFlags features) {
    for (VkFormat format : candidates) {
        VkFormatProperties props;
        vkGetPhysicalDeviceFormatProperties(device.getPhysicalDevice(), format, &props);

        if (tiling == VK_IMAGE_TILING_LINEAR && (props.linearTilingFeatures & features) == features) {
            return format;
        } else if (tiling == VK_IMAGE_TILING_OPTIMAL && (props.optimalTilingFeatures & features) == features) {
            return format;
        }
    }

    throw std::runtime_error("failed to find supported format!");
}

VkImageView &DepthResources::getDepthImageView()
{
    return depthImageView;
}
