//
// Created by arthur on 09/10/2020.
//

#include "Window.hpp"
#include <exception>

#include "../Model/Model.hpp"

Window::Window()
{
}

void Window::init(HINSTANCE hinstance)
{
    this->createWindow(hinstance, WndProc);

    this->instance = new Instance();
    this->debugMessenger = new DebugMessenger(*this->instance);
    this->surface = new Surface(*this, *this->instance);
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

void Window::start()
{
    MSG msg;
    bool quit = false;
    while (!quit) {
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            if (msg.message == WM_QUIT) {
                quit = true;
            }
        }
        this->keyManagement();

        this->drawFrame();
    }

    // Flush device to make sure all resources can be freed if application is about to close
    vkDeviceWaitIdle(this->device->getDevice());
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
    vkDestroyImageView(this->device->getDevice(), this->depthResources->getDepthImageView(), nullptr);
    vkDestroyImage(this->device->getDevice(), this->depthResources->getDepthImage(), nullptr);
    vkFreeMemory(this->device->getDevice(), this->depthResources->getDepthImageMemory(), nullptr);

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

    vkDestroySampler(this->device->getDevice(), this->textureSampler->getTextureSampler(), nullptr);
    vkDestroyImageView(this->device->getDevice(), this->textureImageView->getTextureImageView(), nullptr);

    vkDestroyImage(this->device->getDevice(), this->textureImage->getTextureImage(), nullptr);
    vkFreeMemory(this->device->getDevice(), this->textureImage->getTextureImageMemory(), nullptr);

    vkDestroyDescriptorSetLayout(this->device->getDevice(), this->descriptorSetLayout->getDescriptorSetLayout(), nullptr);

    vkDestroyBuffer(this->device->getDevice(), this->vertexBuffer->getIndexBuffer(), nullptr);
    vkFreeMemory(this->device->getDevice(), this->vertexBuffer->getIndexBufferMemory(), nullptr);

    vkDestroyBuffer(this->device->getDevice(), this->vertexBuffer->getVertexBuffer(), nullptr);
    vkFreeMemory(this->device->getDevice(), this->vertexBuffer->getVertexBufferMemory(), nullptr);

    for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
        vkDestroySemaphore(this->device->getDevice(), this->semaphore->getRenderFinishedSemaphores()[i], nullptr);
        vkDestroySemaphore(this->device->getDevice(), this->semaphore->getImageAvailableSemaphores()[i], nullptr);
        vkDestroyFence(this->device->getDevice(), this->semaphore->getInFlightFences()[i], nullptr);
    }

    vkDestroyCommandPool(this->device->getDevice(), this->commandPool->getCommandPool(), nullptr);

    vkDestroyDevice(this->device->getDevice(), nullptr);

    if (DebugMessenger::ENABLEVALIDATIONLAYERS) {
        this->debugMessenger->release(*this->instance, nullptr);
    }

    vkDestroySurfaceKHR(this->instance->getVkInstance(), this->surface->getSurface(), nullptr);
    vkDestroyInstance(this->instance->getVkInstance(), nullptr);
}

void Window::recreateSwapChain()
{
    int width = 0, height = 0;

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



HWND Window::createWindow(HINSTANCE hinstance, WNDPROC wndproc)
{
    this->windowInstance = hinstance;

    bool fullscreen = false;

    AllocConsole();
    SetConsoleTitle(TEXT("VULKAN_TUTORIAL"));

    WNDCLASSEX wndClass;

    wndClass.cbSize = sizeof(WNDCLASSEX);
    wndClass.style = CS_HREDRAW | CS_VREDRAW;
    wndClass.lpfnWndProc = wndproc;
    wndClass.cbClsExtra = 0;
    wndClass.cbWndExtra = 0;
    wndClass.hInstance = hinstance;
    wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wndClass.lpszMenuName = NULL;
    wndClass.lpszClassName = "VULKAN_TUTORIAL";
    wndClass.hIconSm = LoadIcon(NULL, IDI_WINLOGO);

    if (!RegisterClassEx(&wndClass))
    {
        std::cout << "Could not register window class!\n";
        fflush(stdout);
        exit(1);
    }

    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);

    if (fullscreen)
    {
        DEVMODE dmScreenSettings;
        memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
        dmScreenSettings.dmSize = sizeof(dmScreenSettings);
        dmScreenSettings.dmPelsWidth = screenWidth;
        dmScreenSettings.dmPelsHeight = screenHeight;
        dmScreenSettings.dmBitsPerPel = 32;
        dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
    }

    DWORD dwExStyle;
    DWORD dwStyle;

    if (fullscreen)
    {
        dwExStyle = WS_EX_APPWINDOW;
        dwStyle = WS_POPUP | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
    }
    else
    {
        dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
        dwStyle = WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
    }

    RECT windowRect;
    windowRect.left = 0L;
    windowRect.top = 0L;
    windowRect.right = fullscreen ? (long)screenWidth : (long)windowSize.width;
    windowRect.bottom = fullscreen ? (long)screenHeight : (long)windowSize.height;

    AdjustWindowRectEx(&windowRect, dwStyle, FALSE, dwExStyle);

    this->hwnd = CreateWindowEx(0,
                            "VULKAN_TUTORIAL",
                            "VULKAN TUTORIAL 01",
                            dwStyle | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
                            0,
                            0,
                            windowRect.right - windowRect.left,
                            windowRect.bottom - windowRect.top,
                            NULL,
                            NULL,
                            hinstance,
                            NULL);

    if (!fullscreen)
    {
        // Center on screen
        uint32_t x = (GetSystemMetrics(SM_CXSCREEN) - windowRect.right) / 2;
        uint32_t y = (GetSystemMetrics(SM_CYSCREEN) - windowRect.bottom) / 2;
        SetWindowPos(this->hwnd, 0, x, y, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
    }

    if (!this->hwnd)
    {
        printf("Could not create window!\n");
        fflush(stdout);
        return 0;
        exit(1);
    }

    ShowWindow(this->hwnd, SW_SHOW);
    SetForegroundWindow(this->hwnd);
    SetFocus(this->hwnd);

    return this->hwnd;
}

HWND &Window::getHwnd()
{
    return hwnd;
}

HINSTANCE &Window::getWindowInstance()
{
    return windowInstance;
}

void Window::addKey(int value, std::function<void()> &f)
{
    this->keyVector.push_back(std::make_pair(value, f));
}

void Window::keyManagement()
{
    for (auto &i : this->keyVector) {
        if (GetKeyState(i.first) < 0) {
            i.second();
        }
    }
}
