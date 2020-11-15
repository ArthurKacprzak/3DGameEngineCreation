//
// Created by arthur on 19/10/2020.
//

#ifndef INC_3DGAMEENGINECREATION_DEPTHRESOURCES_HPP
#define INC_3DGAMEENGINECREATION_DEPTHRESOURCES_HPP

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Device.hpp"
#include "ImageViews.hpp"
#include "TextureImage.hpp"
#include "TextureImageView.hpp"

class DepthResources
{
public:
    DepthResources(Device &device, ImageViews &imageViews);
    void release(Device &device);

public:
    static VkFormat findDepthFormat(Device &device);

public:
    VkImageView &getDepthImageView();

    VkImage &getDepthImage();

    VkDeviceMemory &getDepthImageMemory();

private:
    static VkFormat findSupportedFormat(Device &device, const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
private:
    VkImage depthImage;
    VkDeviceMemory depthImageMemory;
    VkImageView depthImageView;
};


#endif //INC_3DGAMEENGINECREATION_DEPTHRESOURCES_HPP
