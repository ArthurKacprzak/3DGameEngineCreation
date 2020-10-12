//
// Created by arthur on 09/10/2020.
//

#ifndef INC_3DGAMEENGINECREATION_WINDOW_HPP
#define INC_3DGAMEENGINECREATION_WINDOW_HPP

#include <iostream>
#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <stdexcept>
#include <cstdlib>

#include "../Surface/Surface.hpp"
#include "../Device/Device.hpp"
#include "../SwapChain/SwapChain.hpp"
#include "../ImageViews/ImageViews.hpp"
#include "../GraphicsPipeline/GraphicsPipeline.hpp"
#include "../Framebuffers/Framebuffers.hpp"
#include "../CommandPool/CommandPool.hpp"
#include "../CommandBuffers/CommandBuffers.hpp"
#include "../Semaphore/Semaphore.hpp"

class Window
{
public:
    static const int WIDTH = 800;
    static const int HEIGHT = 600;

    static const int MAX_FRAMES_IN_FLIGHT = 2;
public:
    Window();
    ~Window();

public:
    void start();
private:
    GLFWwindow *window;

    Instance *instance;
    Surface *surface;
    Device *device;
    SwapChain *swapChain;
    ImageViews *imageViews;
    GraphicsPipeline *graphicsPipeline;
    Framebuffers *framebuffers;
    CommandPool *commandPool;
    CommandBuffers *commandBuffers;
    Semaphore *semaphore;
    size_t currentFrame = 0;

private:
    void drawFrame();
};


#endif //INC_3DGAMEENGINECREATION_WINDOW_HPP
