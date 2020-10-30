//
// Created by arthur on 10/10/2020.
//

#ifndef INC_3DGAMEENGINECREATION_IMAGEVIEWS_HPP
#define INC_3DGAMEENGINECREATION_IMAGEVIEWS_HPP


#include <vulkan/vulkan.h>
#include <vector>
#include "../../Compute/Device/Device.hpp"

class ImageViews
{
public:
    ImageViews();
    void init(Device &device);

public:
    void swapChainImagesResize(uint32_t imageCount);
    std::vector<VkImage> &getSwapChainImages();
    void setSwapChainImageFormat(VkFormat format);
    void setSwapChainExtent(const VkExtent2D &extent);

    VkExtent2D &getSwapChainExtent();
    VkFormat &getSwapChainImageFormat();
    std::vector<VkImageView> &getSwapChainImageViews();

private:
    std::vector<VkImage> swapChainImages;
    VkFormat swapChainImageFormat;
    VkExtent2D swapChainExtent;

    std::vector<VkImageView> swapChainImageViews;
public:
};


#endif //INC_3DGAMEENGINECREATION_IMAGEVIEWS_HPP
