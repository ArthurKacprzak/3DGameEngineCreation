//
// Created by arthur on 09/10/2020.
//

#include "Window.hpp"
#include <exception>

#include "Model.hpp"

Window *w;

static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_CLOSE: {
            DestroyWindow(hWnd);
            PostQuitMessage(0);
            break;
        }
        case WM_MOUSEMOVE:
        {
            w->handleMouseMove(LOWORD(lParam), HIWORD(lParam));
            break;
        }

        case WM_LBUTTONDOWN:
            w->mousePos = Math::vec2((float)LOWORD(lParam), (float)HIWORD(lParam));
            w->mouseButtons.left = true;
            break;
        case WM_RBUTTONDOWN:
            w->mousePos = Math::vec2((float)LOWORD(lParam), (float)HIWORD(lParam));
            w->mouseButtons.right = true;
            break;
        case WM_MBUTTONDOWN:
            w->mousePos = Math::vec2((float)LOWORD(lParam), (float)HIWORD(lParam));
            w->mouseButtons.middle = true;
            break;
        case WM_LBUTTONUP:
            w->mouseButtons.left = false;
            break;
        case WM_RBUTTONUP:
            w->mouseButtons.right = false;
            break;
        case WM_MBUTTONUP:
            w->mouseButtons.middle = false;
            break;
        case WM_MOUSEWHEEL:
        {
            short wheelDelta = GET_WHEEL_DELTA_WPARAM(wParam);
            w->handleMouseWheel(wheelDelta);
            break;
        }

        case WM_KEYDOWN:

            w->handleKeyDown((uint32_t)wParam);
            break;
        case WM_KEYUP:
            w->handleKeyUp((uint32_t)wParam);
            break;
        default:
            break;
    }

    return (DefWindowProc(hWnd, uMsg, wParam, lParam));
}

Window::Window()
{
}

void Window::init(HINSTANCE hinstance)
{
    w = this;
    this->createWindow(hinstance, WndProc);

    this->instance = std::make_unique<Instance>();
    this->debugMessenger = std::make_unique<DebugMessenger>(*this->instance);
    this->surface = std::make_unique<Surface>(*this, *this->instance);
    this->device = std::make_unique<Device>(*this->instance, *this->surface);
    this->graphics.imageViews = std::make_unique<ImageViews>();
    this->graphics.swapChain = std::make_unique<SwapChain>(*this, *this->device, *this->surface, *this->graphics.imageViews);
    this->graphics.imageViews->init(*this->device);

    this->graphics.descriptorSetLayout = std::make_unique<DescriptorSetLayout>(*this->device); //
    this->graphics.graphicsPipeline = std::make_unique<GraphicsPipeline>(*this->device, *this->graphics.imageViews, *this->graphics.descriptorSetLayout);


    this->commandPool = std::make_unique<CommandPool>(*this->device, *this->surface);
    this->graphics.depthResources = std::make_unique<DepthResources>(*this->device, *this->graphics.imageViews);
    this->framebuffers = std::make_unique<Framebuffers>(*this->graphics.imageViews, *this->device, *this->graphics.graphicsPipeline, *this->graphics.depthResources);
    this->graphics.textureImage = std::make_unique<TextureImage>(*this->device, *this->commandPool);
    this->graphics.textureImageView = std::make_unique<TextureImageView>(*this->device, *this->graphics.textureImage);
    this->graphics.textureSampler = std::make_unique<TextureSampler>(*this->device);

    this->graphics.vertexBuffer = std::make_unique<VertexBuffer>(*this->device, *this->commandPool, this->vertices, this->indices);

    this->graphics.uniformBuffers = std::make_unique<UniformBuffers>(*this->device, *this->graphics.imageViews);

    this->graphics.descriptorPool = std::make_unique<DescriptorPool>(*this->device, *this->graphics.imageViews);
    this->graphics.descriptorSets = std::make_unique<DescriptorSets>(*this->device, *this->graphics.imageViews, *this->graphics.descriptorSetLayout,
                                              *this->graphics.uniformBuffers, *this->graphics.descriptorPool, *this->graphics.textureImageView, *this->graphics.textureSampler);

    this->model = std::make_unique<Model>();
    this->commandBuffers = std::make_unique<CommandBuffers>(this, *this->graphics.imageViews, *this->device, *this->commandPool, *this->framebuffers,
                                              *this->graphics.graphicsPipeline, *this->graphics.vertexBuffer,
                                              *this->graphics.descriptorSets, *this->graphics.descriptorSetLayout);

    this->semaphore = std::make_unique<Semaphore>(*this->graphics.imageViews, *this->device);

    this->graphics.camera = std::make_unique<Camera>();

    this->graphics.camera->setPosition(Math::vec3(0, 0, -1));
    this->graphics.camera->setRotation(Math::vec3(0, 0.0f, 90));
    this->graphics.camera->setPerspective(30.0f, this->graphics.imageViews->getSwapChainExtent().width / (float) this->graphics.imageViews->getSwapChainExtent().height, 0.1f, 10.0f);
}

void Window::start()
{
    MSG msg;
    bool quit = false;
    while (!quit) {
        while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            if (msg.message == WM_QUIT) {
                quit = true;
            }
        }
        this->drawFrame();
    }

    // Flush device to make sure all resources can be freed if application is about to close
    vkDeviceWaitIdle(this->device->getDevice());
    this->cleanup();
}

void Window::drawFrame()
{
    vkWaitForFences(this->device->getDevice(), 1, &this->semaphore->getInFlightFences()[this->currentFrame], VK_TRUE, UINT64_MAX);

    uint32_t imageIndex;
    VkResult result = vkAcquireNextImageKHR(this->device->getDevice(), this->graphics.swapChain->getSwapChain(), UINT64_MAX, this->semaphore->getImageAvailableSemaphores()[this->currentFrame], VK_NULL_HANDLE, &imageIndex);

    if (result == VK_ERROR_OUT_OF_DATE_KHR) {
        this->recreateSwapChain();
        return;
    } else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
        throw std::runtime_error("failed to acquire swap chain image!");
    }





    this->updateUniformBuffer(imageIndex);



    auto tStart = std::chrono::high_resolution_clock::now();

    auto tEnd = std::chrono::high_resolution_clock::now();
    auto tDiff = std::chrono::duration<double, std::milli>(tEnd - tStart).count();
    float frameTimer = (float)tDiff / 1000.0f;
    this->graphics.camera->update(frameTimer);


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

    VkSwapchainKHR swapChains[] = {this->graphics.swapChain->getSwapChain()};
    presentInfo.swapchainCount = 1;
    presentInfo.pSwapchains = swapChains;

    presentInfo.pImageIndices = &imageIndex;

    result = vkQueuePresentKHR(this->device->getPresentQueue(), &presentInfo);

    if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || this->framebufferResized) {
        this->framebufferResized = false;
    } else if (result != VK_SUCCESS) {
        throw std::runtime_error("failed to present swap chain image!");
    }

    this->currentFrame = (this->currentFrame + 1) % MAX_FRAMES_IN_FLIGHT;
}

void Window::handleMouseMove(int32_t x, int32_t y)
{
    int32_t dx = (int32_t)this->mousePos.pos[0] - x;
    int32_t dy = (int32_t)this->mousePos.pos[1] - y;


    if (mouseButtons.left) {
        this->graphics.camera->rotate(Math::vec3(dy * this->graphics.camera->rotationSpeed, 0.0f, -dx * this->graphics.camera->rotationSpeed));
    }
    if (mouseButtons.right) {
        this->graphics.camera->translate(Math::vec3(-0.0f, 0.0f, dy * .005f));
    }
    if (mouseButtons.middle) {
        this->graphics.camera->translate(Math::vec3(-dy * 0.01f, dx * 0.01f, 0.0f));
    }


    this->mousePos = Math::vec2((float)x, (float)y);
}

void Window::updateUniformBuffer(uint32_t currentImage)
{
    static auto startTime = std::chrono::high_resolution_clock::now();

    auto currentTime = std::chrono::high_resolution_clock::now();
    float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();

    UniformBuffers::UniformBufferObject ubo{};


    ubo.proj = this->graphics.camera->matrices.perspective;
    ubo.view = this->graphics.camera->matrices.view;
    ubo.model = Math::scaleMat(Math::mat4(1.0f), Math::vec3(0.2f));

    this->model->model = Math::translateMat(this->model->model, this->moveVector);
    ubo.model = this->model->model;


    ubo.cameraPos = Math::multiplyMat(Math::vec4(this->graphics.camera->position.pos[0], this->graphics.camera->position.pos[1], this->graphics.camera->position.pos[2], -1.0f), -1.0f);

    void* data;
    vkMapMemory(this->device->getDevice(), this->graphics.uniformBuffers->getUniformBuffersMemory()[currentImage], 0, sizeof(ubo), 0, &data);
    memcpy(data, &ubo, sizeof(ubo));
    vkUnmapMemory(this->device->getDevice(), this->graphics.uniformBuffers->getUniformBuffersMemory()[currentImage]);
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
    this->graphics.windowInstance = hinstance;

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
    wndClass.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
    wndClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wndClass.lpszMenuName = nullptr;
    wndClass.lpszClassName = "VULKAN_TUTORIAL";
    wndClass.hIconSm = LoadIcon(nullptr, IDI_WINLOGO);

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
    windowRect.right = fullscreen ? (long)screenWidth : (long)this->graphics.windowSize.width;
    windowRect.bottom = fullscreen ? (long)screenHeight : (long)this->graphics.windowSize.height;

    AdjustWindowRectEx(&windowRect, dwStyle, FALSE, dwExStyle);

    this->graphics.hwnd = CreateWindowEx(0,
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
        SetWindowPos(this->graphics.hwnd, 0, x, y, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
    }

    if (!this->graphics.hwnd)
    {
        printf("Could not create window!\n");
        fflush(stdout);
        return nullptr;
    }

    ShowWindow(this->graphics.hwnd, SW_SHOW);
    SetForegroundWindow(this->graphics.hwnd);
    SetFocus(this->graphics.hwnd);

    return this->graphics.hwnd;
}

HWND &Window::getHwnd()
{
    return this->graphics.hwnd;
}

HINSTANCE &Window::getWindowInstance()
{
    return this->graphics.windowInstance;
}

void Window::addKeyPress(int value, std::function<void()> &f)
{
    this->keyVectorPress.emplace_back(value, f);
}

void Window::addKeyRelease(int value, std::function<void()> &f)
{
    this->keyVectorRelease.emplace_back(value, f);
}

void Window::handleMouseWheel(short wheelDelta)
{
    this->graphics.camera->translate(Math::vec3(0.0f, 0.0f, (float)wheelDelta * 0.005f));
}

void Window::handleKeyDown(uint32_t key)
{
    switch (key)
    {
        case VK_ESCAPE:
            PostQuitMessage(0);
            break;
        default:
            break;
    }

//    std::cout << this->graphics.camera->type << " " << key << " " << (uint32_t)'z' << "\n";
    for (auto &i : this->keyVectorPress) {
        if (key == i.first) {
            i.second();
        }
    }
}

void Window::handleKeyUp(uint32_t key)
{
    for (auto &i : this->keyVectorRelease) {
        if (key == i.first) {
            i.second();
        }
    }
}

Window::~Window()
{
}

void Window::recreateSwapChain()
{

    vkDeviceWaitIdle(this->device->getDevice());

    this->cleanupSwapChain();




    this->graphics.imageViews = std::make_unique<ImageViews>();
    this->graphics.swapChain = std::make_unique<SwapChain>(*this, *this->device, *this->surface, *this->graphics.imageViews);
    this->graphics.imageViews->init(*this->device);

    this->graphics.graphicsPipeline = std::make_unique<GraphicsPipeline>(*this->device, *this->graphics.imageViews, *this->graphics.descriptorSetLayout);

    this->graphics.depthResources = std::make_unique<DepthResources>(*this->device, *this->graphics.imageViews);
    this->framebuffers = std::make_unique<Framebuffers>(*this->graphics.imageViews, *this->device, *this->graphics.graphicsPipeline, *this->graphics.depthResources);






    this->graphics.uniformBuffers = std::make_unique<UniformBuffers>(*this->device, *this->graphics.imageViews);
    this->graphics.descriptorPool = std::make_unique<DescriptorPool>(*this->device, *this->graphics.imageViews);
    this->graphics.descriptorSets = std::make_unique<DescriptorSets>(*this->device, *this->graphics.imageViews, *this->graphics.descriptorSetLayout,
                                                       *this->graphics.uniformBuffers, *this->graphics.descriptorPool, *this->graphics.textureImageView, *this->graphics.textureSampler);
    this->commandBuffers = std::make_unique<CommandBuffers>(this, *this->graphics.imageViews, *this->device, *this->commandPool, *this->framebuffers,
                                              *this->graphics.graphicsPipeline, *this->graphics.vertexBuffer,
                                              *this->graphics.descriptorSets, *this->graphics.descriptorSetLayout);
}

void Window::cleanupSwapChain()
{
    this->graphics.depthResources->release(*this->device);
    this->framebuffers->release(*this->device);
    this->commandBuffers->release(*this->device, *this->commandPool);
    this->graphics.graphicsPipeline->release(*this->device);
    this->graphics.imageViews->release(*this->device);
    this->graphics.swapChain->release(*this->device);
    this->graphics.uniformBuffers->release(*this->device, *this->graphics.imageViews);
    this->graphics.descriptorPool->release(*this->device);

    this->graphics.depthResources.release();
    this->framebuffers.release();
    this->commandBuffers.release();
    this->graphics.graphicsPipeline.release();
    this->graphics.imageViews.release();
    this->graphics.swapChain.release();
    this->graphics.uniformBuffers.release();
    this->graphics.descriptorPool.release();
    this->graphics.descriptorSets.release();
}

void Window::cleanup()
{
    this->cleanupSwapChain();

    this->graphics.textureSampler->release(*this->device);
    this->graphics.textureImageView->release(*this->device);
    this->graphics.textureImage->release(*this->device);
    this->graphics.descriptorSetLayout->release(*this->device);
    this->graphics.vertexBuffer->release(*this->device);
    this->semaphore->release(*this->device);
    this->commandPool->release(*this->device);
    this->device->release();
    if (DebugMessenger::ENABLEVALIDATIONLAYERS) {
        this->debugMessenger->release(*this->instance, nullptr);
    }
    this->surface->release(*this->instance);
    this->instance->release();

    this->graphics.textureSampler.release();
    this->graphics.textureImageView.release();
    this->graphics.textureImage.release();
    this->graphics.descriptorSetLayout.release();
    this->graphics.vertexBuffer.release();
    this->semaphore.release();
    this->commandPool.release();
    this->device.release();
    if (DebugMessenger::ENABLEVALIDATIONLAYERS) {
        this->debugMessenger.release();
    }
    this->surface.release();
    this->instance.release();
}

void Window::setCameraType(Camera::CameraType type)
{
    this->graphics.camera->type = type;
}

void Window::move(struct vec3 vector)
{
    this->moveVector = vector;
}
