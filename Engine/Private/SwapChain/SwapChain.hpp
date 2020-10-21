//
// Created by arthur on 10/10/2020.
//

#ifndef INC_3DGAMEENGINECREATION_SWAPCHAIN_HPP
#define INC_3DGAMEENGINECREATION_SWAPCHAIN_HPP

#include <vulkan/vulkan.h>
#include <vector>
#include "../Device/Device.hpp"
#include "../ImageViews/ImageViews.hpp"

class Surface;
class Window;
class Framebuffers;

class SwapChain
{
public:
    SwapChain(Window &window, Device &device, Surface &surface, ImageViews &imageViews);
public:
    struct SwapChainSupportDetails {
        VkSurfaceCapabilitiesKHR capabilities;
        std::vector<VkSurfaceFormatKHR> formats;
        std::vector<VkPresentModeKHR> presentModes;
    };

public:
    VkSwapchainKHR &getSwapChain();

    static SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device, Surface &surface);

private:
    VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
    VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
    VkExtent2D chooseSwapExtent(Window &window, const VkSurfaceCapabilitiesKHR& capabilities);

private:
    VkSwapchainKHR swapChain;

};


#endif //INC_3DGAMEENGINECREATION_SWAPCHAIN_HPP
