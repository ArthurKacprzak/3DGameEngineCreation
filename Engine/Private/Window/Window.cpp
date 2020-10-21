//
// Created by arthur on 09/10/2020.
//

#include "Window.hpp"

Window::Window()
{

    this->vertices = {

            {{-0.5f, -0.5f, 1.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
            {{0.5f, -0.5f, 1.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
            {{0.5f, 0.5f, 1.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
            {{-0.5f, 0.5f, 1.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}},

            {{-0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
            {{0.5f, -0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
            {{0.5f, 0.5f, -0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
            {{-0.5f, 0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}},

            {{-0.5f, -0.5f, -1.f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
            {{0.5f, -0.5f, -1.f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
            {{0.5f, 0.5f, -1.f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
            {{-0.5f, 0.5f, -1.f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}}
    };

    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    //    this->window = glfwCreateWindow(1920, 1080, "Vulkan window", glfwGetPrimaryMonitor(), nullptr);
    this->window = glfwCreateWindow(Window::WIDTH, Window::HEIGHT, "Vulkan window", nullptr, nullptr);
    glfwSetWindowUserPointer(this->window, this);
    glfwSetFramebufferSizeCallback(this->window, Window::framebufferResizeCallback);

    this->instance = new Instance();
    this->debugMessenger = new DebugMessenger(*this->instance);
    this->surface = new Surface(*this->window, *this->instance);
    this->device = new Device(*this->instance, *this->surface);
    this->imageViews = new ImageViews();
    this->swapChain = new SwapChain(*this, *this->device, *this->surface, *this->imageViews);
    this->imageViews->init(*this->device);

    this->descriptorSetLayout = new DescriptorSetLayout(*this->device); //
    this->graphicsPipeline = new GraphicsPipeline(*this->device, *this->imageViews, *this->descriptorSetLayout);


    this->commandPool = new CommandPool(*this->device, *this->surface);
    this->depthResources = new DepthResources(*this->device, *this->imageViews);
    this->framebuffers = new Framebuffers(*this->imageViews, *this->device, *this->graphicsPipeline, *this->depthResources);
    this->textureImage = new TextureImage(*this->device, *this->commandPool);
    this->textureImageView = new TextureImageView(*this->device, *this->textureImage);
    this->textureSampler = new TextureSampler(*this->device);

    this->model = new Model(this);
    this->vertexBuffer = new VertexBuffer(this, *this->device, *this->commandPool, this->vertices);

    this->uniformBuffers = new UniformBuffers(*this->device, *this->imageViews);

    this->descriptorPool = new DescriptorPool(*this->device, *this->imageViews);
    this->descriptorSets = new DescriptorSets(*this->device, *this->imageViews, *this->descriptorSetLayout,
                                              *this->uniformBuffers, *this->descriptorPool, *this->textureImageView, *this->textureSampler);

    this->commandBuffers = new CommandBuffers(this, *this->imageViews, *this->device, *this->commandPool, *this->framebuffers,
                                              *this->graphicsPipeline, this->vertices, *this->vertexBuffer,
                                              *this->descriptorSets, *this->descriptorSetLayout);

    this->semaphore = new Semaphore(*this->imageViews, *this->device);

}

void Window::framebufferResizeCallback(GLFWwindow* window, int width, int height) {
    auto app = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
    app->framebufferResized = true;
}


void Window::start()
{
    while(!glfwWindowShouldClose(this->window)) {
        glfwPollEvents();
        this->drawFrame();
    }
    this->cleanup();
}

void Window::drawFrame()
{
    vkWaitForFences(this->device->getDevice(), 1, &this->semaphore->getInFlightFences()[this->currentFrame], VK_TRUE, UINT64_MAX);

    uint32_t imageIndex;
    VkResult result = vkAcquireNextImageKHR(this->device->getDevice(), swapChain->getSwapChain(), UINT64_MAX, this->semaphore->getImageAvailableSemaphores()[this->currentFrame], VK_NULL_HANDLE, &imageIndex);

    if (result == VK_ERROR_OUT_OF_DATE_KHR) {
        this->recreateSwapChain();
        return;
    } else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
        throw std::runtime_error("failed to acquire swap chain image!");
    }

    this->updateUniformBuffer(imageIndex);

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

    result = vkQueuePresentKHR(this->device->getPresentQueue(), &presentInfo);

    if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || this->framebufferResized) {
        this->framebufferResized = false;
        this->recreateSwapChain();
    } else if (result != VK_SUCCESS) {
        throw std::runtime_error("failed to present swap chain image!");
    }

    this->currentFrame = (this->currentFrame + 1) % MAX_FRAMES_IN_FLIGHT;
}

void Window::updateUniformBuffer(uint32_t currentImage)
{
    static auto startTime = std::chrono::high_resolution_clock::now();

    auto currentTime = std::chrono::high_resolution_clock::now();
    float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();

    UniformBuffers::UniformBufferObject ubo{};
    ubo.model = glm::rotate(glm::mat4(1.0f), time * glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    ubo.view = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    ubo.proj = glm::perspective(glm::radians(45.0f), this->imageViews->getSwapChainExtent().width / (float) this->imageViews->getSwapChainExtent().height, 0.1f, 10.0f);
    ubo.proj[1][1] *= -1;

    void* data;
    vkMapMemory(this->device->getDevice(), this->uniformBuffers->getUniformBuffersMemory()[currentImage], 0, sizeof(ubo), 0, &data);
    memcpy(data, &ubo, sizeof(ubo));
    vkUnmapMemory(this->device->getDevice(), this->uniformBuffers->getUniformBuffersMemory()[currentImage]);
}

void Window::cleanupSwapChain()
{
    for (size_t i = 0; i < this->framebuffers->getSwapChainFramebuffers().size(); i++) {
        vkDestroyFramebuffer(this->device->getDevice(), this->framebuffers->getSwapChainFramebuffers()[i], nullptr);
    }

    vkFreeCommandBuffers(this->device->getDevice(), this->commandPool->getCommandPool(), static_cast<uint32_t>(this->commandBuffers->getCommandBuffers().size()), this->commandBuffers->getCommandBuffers().data());

    vkDestroyPipeline(this->device->getDevice(), this->graphicsPipeline->getGraphicsPipeline(), nullptr);
    vkDestroyPipelineLayout(this->device->getDevice(), this->graphicsPipeline->getPipelineLayout(), nullptr);
    vkDestroyRenderPass(this->device->getDevice(), this->graphicsPipeline->getRenderPass(), nullptr);

    for (size_t i = 0; i < this->imageViews->getSwapChainImageViews().size(); i++) {
        vkDestroyImageView(this->device->getDevice(), this->imageViews->getSwapChainImageViews()[i], nullptr);
    }

    vkDestroySwapchainKHR(this->device->getDevice(), this->swapChain->getSwapChain(), nullptr);

    for (size_t i = 0; i < this->imageViews->getSwapChainImages().size(); i++) {
        vkDestroyBuffer(this->device->getDevice(), this->uniformBuffers->getUniformBuffers()[i], nullptr);
        vkFreeMemory(this->device->getDevice(), this->uniformBuffers->getUniformBuffersMemory()[i], nullptr);
    }

    vkDestroyDescriptorPool(this->device->getDevice(), this->descriptorPool->getDescriptorPool(), nullptr);
}

void Window::cleanup() {
    this->cleanupSwapChain();

    vkDestroyDescriptorSetLayout(this->device->getDevice(), this->descriptorSetLayout->getDescriptorSetLayout(), nullptr);

    vkDestroyBuffer(this->device->getDevice(), this->vertexBuffer->getVertexBuffer(), nullptr);
    vkFreeMemory(this->device->getDevice(), this->vertexBuffer->getVertexBufferMemory(), nullptr);

    for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
        vkDestroySemaphore(this->device->getDevice(), this->semaphore->getRenderFinishedSemaphores()[i], nullptr);
        vkDestroySemaphore(this->device->getDevice(), this->semaphore->getImageAvailableSemaphores()[i], nullptr);
        vkDestroyFence(this->device->getDevice(), this->semaphore->getInFlightFences()[i], nullptr);
    }

    vkDestroyCommandPool(this->device->getDevice(), this->commandPool->getCommandPool(), nullptr);

    vkDestroyDevice(this->device->getDevice(), nullptr);

    vkDestroySurfaceKHR(this->instance->getVkInstance(), this->surface->getSurface(), nullptr);
    vkDestroyInstance(this->instance->getVkInstance(), nullptr);

    glfwDestroyWindow(this->window);

    glfwTerminate();
}

void Window::recreateSwapChain()
{
    int width = 0, height = 0;
    glfwGetFramebufferSize(this->window, &width, &height);
    while (width == 0 || height == 0) {
        glfwGetFramebufferSize(this->window, &width, &height);
        glfwWaitEvents();
    }

    vkDeviceWaitIdle(device->getDevice());

    this->cleanupSwapChain();

    this->swapChain = new SwapChain(*this, *this->device, *this->surface, *this->imageViews);
    this->imageViews->init(*this->device);
    this->graphicsPipeline = new GraphicsPipeline(*this->device, *this->imageViews, *this->descriptorSetLayout);
    this->depthResources = new DepthResources(*this->device, *this->imageViews);
    this->framebuffers = new Framebuffers(*this->imageViews, *this->device, *this->graphicsPipeline, *this->depthResources);
    this->uniformBuffers = new UniformBuffers(*this->device, *this->imageViews);
    this->descriptorPool = new DescriptorPool(*this->device, *this->imageViews);
    this->descriptorSets = new DescriptorSets(*this->device, *this->imageViews, *this->descriptorSetLayout, *this->uniformBuffers, *this->descriptorPool, *this->textureImageView, *this->textureSampler);
    this->commandBuffers = new CommandBuffers(this, *this->imageViews, *this->device, *this->commandPool, *this->framebuffers,
                                              *this->graphicsPipeline, this->vertices, *this->vertexBuffer, *this->descriptorSets,
                                              *this->descriptorSetLayout);
}

Window::~Window()
{
    this->surface->release(*this->instance);
    delete this->instance;
    delete this->device;
    glfwDestroyWindow(this->window);

    glfwTerminate();
}

GLFWwindow *Window::getWindow()
{
    return window;
}

void Window::addVertice(Vertex &data)
{
    this->vertices.push_back(data);
}

std::vector<Vertex> &Window::getVertices()
{
    return this->vertices;
}

std::vector<uint32_t> &Window::getIndices()
{
    return this->indices;
}

void Window::addIndex(uint32_t data)
{
    this->indices.push_back(data);
}
