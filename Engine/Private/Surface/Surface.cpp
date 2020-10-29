//
// Created by arthur on 10/10/2020.
//

#include "Surface.hpp"
#include "../Window/Window.hpp"
#include <vulkan/vulkan_win32.h>

Surface::Surface(Window &window, Instance &instance)
{
    VkWin32SurfaceCreateInfoKHR surfaceCreateInfo;
    surfaceCreateInfo.hinstance = (HINSTANCE)window.getWindowInstance();
    surfaceCreateInfo.hwnd = (HWND)window.getHwnd();
    surfaceCreateInfo.flags = 0;
    surfaceCreateInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;

    if (vkCreateWin32SurfaceKHR(instance.getVkInstance(), &surfaceCreateInfo, nullptr, &this->surface) != VK_SUCCESS) {
        throw std::runtime_error("failed to create window surface!");
    }
}

Surface::~Surface()
{
}

VkSurfaceKHR &Surface::getSurface()
{
    return this->surface;
}

void Surface::release(Instance &instance)
{
    vkDestroySurfaceKHR(instance.getVkInstance(), surface, nullptr);
    delete this;
}
