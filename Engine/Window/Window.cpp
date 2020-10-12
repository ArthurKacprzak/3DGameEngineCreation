//
// Created by arthur on 09/10/2020.
//

#include "Window.hpp"

Window::Window()
{
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
//    this->window = glfwCreateWindow(1920, 1080, "Vulkan window", glfwGetPrimaryMonitor(), nullptr);
    this->window = glfwCreateWindow(Window::WIDTH, Window::HEIGHT, "Vulkan window", nullptr, nullptr);

    this->instance = new Instance();
    this->surface = new Surface(*this->window, *this->instance);
    this->device = new Device(*this->instance, *this->surface);
    this->imageViews = new ImageViews();
    this->swapChain = new SwapChain(*this->device, *this->surface, *this->imageViews);
    this->imageViews->init(*this->device);
    this->graphicsPipeline = new GraphicsPipeline(*this->device, *this->imageViews);
    this->framebuffers = new Framebuffers(*this->imageViews, *this->device, *this->graphicsPipeline);
    this->commandPool = new CommandPool(*this->device, *this->surface);
    this->commandBuffers = new CommandBuffers(*this->imageViews, *this->device, *this->commandPool, *this->framebuffers, *this->graphicsPipeline);
    this->semaphore = new Semaphore(*this->imageViews, *this->device);
}


void Window::start()
{
    while(!glfwWindowShouldClose(this->window)) {
        glfwPollEvents();
        this->drawFrame();
    }
}

void Window::drawFrame()
{
    vkWaitForFences(this->device->getDevice(), 1, &this->semaphore->getInFlightFences()[this->currentFrame], VK_TRUE, UINT64_MAX);

    uint32_t imageIndex;
    vkAcquireNextImageKHR(this->device->getDevice(), swapChain->getSwapChain(), UINT64_MAX, this->semaphore->getImageAvailableSemaphores()[this->currentFrame], VK_NULL_HANDLE, &imageIndex);

    if (this->semaphore->getImagesInFlight()[imageIndex] != VK_NULL_HANDLE) {
        vkWaitForFences(this->device->getDevice(), 1, &this->semaphore->getImagesInFlight()[imageIndex], VK_TRUE, UINT64_MAX);
    }
    this->semaphore->getImagesInFlight()[imageIndex] = this->semaphore->getInFlightFences()[this->currentFrame];

    VkSubmitInfo submitInfo{};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

    VkSemaphore waitSemaphores[] = {this->semaphore->getImageAvailableSemaphores()[this->currentFrame]};
    VkPipelineStageFlags waitStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
    submitInfo.waitSemaphoreCount = 1;
    submitInfo.pWaitSemaphores = waitSemaphores;
    submitInfo.pWaitDstStageMask = waitStages;

    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &this->commandBuffers->getCommandBuffers()[imageIndex];

    VkSemaphore signalSemaphores[] = {this->semaphore->getRenderFinishedSemaphores()[this->currentFrame]};
    submitInfo.signalSemaphoreCount = 1;
    submitInfo.pSignalSemaphores = signalSemaphores;

    vkResetFences(device->getDevice(), 1, &this->semaphore->getInFlightFences()[this->currentFrame]);

    if (vkQueueSubmit(this->device->getGraphicsQueue(), 1, &submitInfo, this->semaphore->getInFlightFences()[this->currentFrame]) != VK_SUCCESS) {
        throw std::runtime_error("failed to submit draw command buffer!");
    }

    VkPresentInfoKHR presentInfo{};
    presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

    presentInfo.waitSemaphoreCount = 1;
    presentInfo.pWaitSemaphores = signalSemaphores;

    VkSwapchainKHR swapChains[] = {swapChain->getSwapChain()};
    presentInfo.swapchainCount = 1;
    presentInfo.pSwapchains = swapChains;

    presentInfo.pImageIndices = &imageIndex;

    vkQueuePresentKHR(this->device->getPresentQueue(), &presentInfo);

    this->currentFrame = (this->currentFrame + 1) % MAX_FRAMES_IN_FLIGHT;
}

Window::~Window()
{
    this->surface->release(*this->instance);
    delete this->instance;
    delete this->device;
    glfwDestroyWindow(this->window);

    glfwTerminate();
}
