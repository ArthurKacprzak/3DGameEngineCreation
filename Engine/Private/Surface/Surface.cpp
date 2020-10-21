//
// Created by arthur on 10/10/2020.
//

#include "Surface.hpp"

Surface::Surface(GLFWwindow &window, Instance &instance)
{

    if (glfwCreateWindowSurface(instance.getVkInstance(), &window, nullptr, &this->surface) != VK_SUCCESS) {
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
