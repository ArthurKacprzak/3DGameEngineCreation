//
// Created by arthur on 09/10/2020.
//

#include "Window.hpp"
#include <exception>

#include "../Graphics/Model/Model.hpp"

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
            w->mousePos = glm::vec2((float)LOWORD(lParam), (float)HIWORD(lParam));
            w->mouseButtons.left = true;
            break;
        case WM_RBUTTONDOWN:
            w->mousePos = glm::vec2((float)LOWORD(lParam), (float)HIWORD(lParam));
            w->mouseButtons.right = true;
            break;
        case WM_MBUTTONDOWN:
            w->mousePos = glm::vec2((float)LOWORD(lParam), (float)HIWORD(lParam));
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

    this->instance = new Instance();
    this->debugMessenger = new DebugMessenger(*this->instance);
    this->surface = new Surface(*this, *this->instance);
    this->device = new Device(*this->instance, *this->surface);
    this->graphics.imageViews = new ImageViews();
    this->graphics.swapChain = new SwapChain(*this, *this->device, *this->surface, *this->graphics.imageViews);
    this->graphics.imageViews->init(*this->device);

    this->graphics.descriptorSetLayout = new DescriptorSetLayout(*this->device); //
    this->graphics.graphicsPipeline = new GraphicsPipeline(*this->device, *this->graphics.imageViews, *this->graphics.descriptorSetLayout);


    this->commandPool = new CommandPool(*this->device, *this->surface);
    this->graphics.depthResources = new DepthResources(*this->device, *this->graphics.imageViews);
    this->framebuffers = new Framebuffers(*this->graphics.imageViews, *this->device, *this->graphics.graphicsPipeline, *this->graphics.depthResources);
    this->graphics.textureImage = new TextureImage(*this->device, *this->commandPool);
    this->graphics.textureImageView = new TextureImageView(*this->device, *this->graphics.textureImage);
    this->graphics.textureSampler = new TextureSampler(*this->device);

    this->model = new Model(this);
    this->graphics.vertexBuffer = new VertexBuffer(this, *this->device, *this->commandPool, this->vertices);

    this->graphics.uniformBuffers = new UniformBuffers(*this->device, *this->graphics.imageViews);

    this->graphics.descriptorPool = new DescriptorPool(*this->device, *this->graphics.imageViews);
    this->graphics.descriptorSets = new DescriptorSets(*this->device, *this->graphics.imageViews, *this->graphics.descriptorSetLayout,
                                              *this->graphics.uniformBuffers, *this->graphics.descriptorPool, *this->graphics.textureImageView, *this->graphics.textureSampler);

    this->commandBuffers = new CommandBuffers(this, *this->graphics.imageViews, *this->device, *this->commandPool, *this->framebuffers,
                                              *this->graphics.graphicsPipeline, this->vertices, *this->graphics.vertexBuffer,
                                              *this->graphics.descriptorSets, *this->graphics.descriptorSetLayout);

    this->semaphore = new Semaphore(*this->graphics.imageViews, *this->device);

    this->graphics.camera = new Camera();

    this->graphics.camera->type = Camera::CameraType::firstperson;
    this->graphics.camera->setPosition(glm::vec3(0, 0, -1));
    this->graphics.camera->setRotation(glm::vec3(0, 0.0f, 90));
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
    VkResult result = vkAcquireNextImageKHR(this->device->getDevice(), this->graphics.swapChain->getSwapChain(), UINT64_MAX, this->semaphore->getImageAvailableSemaphores()[this->currentFrame], VK_NULL_HANDLE, &imageIndex);

    if (result == VK_ERROR_OUT_OF_DATE_KHR) {
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
    int32_t dx = (int32_t)this->mousePos.x - x;
    int32_t dy = (int32_t)this->mousePos.y - y;


    if (mouseButtons.left) {
        this->graphics.camera->rotate(glm::vec3(dy * this->graphics.camera->rotationSpeed, -dx * this->graphics.camera->rotationSpeed, 0.0f));
    }
    if (mouseButtons.right) {
        this->graphics.camera->translate(glm::vec3(-0.0f, 0.0f, dy * .005f));
    }
    if (mouseButtons.middle) {
        this->graphics.camera->translate(glm::vec3(-dx * 0.01f, -dy * 0.01f, 0.0f));
    }


    this->mousePos = glm::vec2((float)x, (float)y);
}

void Window::updateUniformBuffer(uint32_t currentImage)
{
    static auto startTime = std::chrono::high_resolution_clock::now();

    auto currentTime = std::chrono::high_resolution_clock::now();
    float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();

    UniformBuffers::UniformBufferObject ubo{};
/*    ubo.model = glm::scale(glm::mat4(1.0f), glm::vec3(0.2f));
    ubo.view = glm::lookAt(glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    ubo.proj = glm::perspective(glm::radians(30.0f), this->imageViews->getSwapChainExtent().width / (float) this->imageViews->getSwapChainExtent().height, 0.1f, 10.0f);
    ubo.proj[1][1] *= -1;*/

    ubo.proj = this->graphics.camera->matrices.perspective;
    ubo.view = this->graphics.camera->matrices.view;
    ubo.model = glm::scale(glm::mat4(1.0f), glm::vec3(0.2f));

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

    bool fullscreen = true;

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

void Window::addKey(int value, std::function<void()> &f)
{
    this->keyVector.emplace_back(value, f);
}

void Window::keyManagement()
{
    for (auto &i : this->keyVector) {
        if (GetKeyState(i.first) < 0) {
            i.second();
        }
    }
}

void Window::handleMouseWheel(short wheelDelta)
{
    this->graphics.camera->translate(glm::vec3(0.0f, 0.0f, (float)wheelDelta * 0.005f));
}

Window::~Window()
{
    this->surface->release(*this->instance);
    delete this->instance;
    delete this->device;
}
