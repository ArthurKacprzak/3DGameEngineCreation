//
// Created by arthur on 10/10/2020.
//

#ifndef INC_3DGAMEENGINECREATION_SURFACE_HPP
#define INC_3DGAMEENGINECREATION_SURFACE_HPP

#include "../Instance/Instance.hpp"

#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>

class Surface
{
public:
    Surface(GLFWwindow &window, Instance &instance);
    void release(Instance &instance);
    ~Surface();

private:
    VkSurfaceKHR surface;
private:
public:
    VkSurfaceKHR &getSurface();
};


#endif //INC_3DGAMEENGINECREATION_SURFACE_HPP
