//
// Created by arthur on 09/10/2020.
//

#ifndef INC_3DGAMEENGINECREATION_WINDOW_HPP
#define INC_3DGAMEENGINECREATION_WINDOW_HPP

#include <vulkan/vulkan.h>
#include <windows.h>
#include <stdexcept>
#include <cstdlib>

#include <chrono>

#include "Surface.hpp"
#include "Device.hpp"
#include "CommandPool.hpp"
#include "CommandBuffers.hpp"
#include "Semaphore.hpp"
#include "DebugMessenger.hpp"

#include "SwapChain.hpp"
#include "ImageViews.hpp"
#include "GraphicsPipeline.hpp"
#include "DescriptorSetLayout.hpp"
#include "DescriptorSets.hpp"
#include "Framebuffers.hpp"
#include "Vertex.hpp"
#include "VertexBuffer.hpp"
#include "UniformBuffers.hpp"
#include "DescriptorPool.hpp"
#include "TextureImage.hpp"
#include "TextureImageView.hpp"
#include "TextureSampler.hpp"
#include "DepthResources.hpp"

#include "Camera.hpp"
#include "Math.hpp"

class Window
{
public:
    static const int MAX_FRAMES_IN_FLIGHT = 2;

public:
    Window();
    ~Window();

public:
    void start();
    void init(HINSTANCE hInstance);

    struct {
        bool left = false;
        bool right = false;
        bool middle = false;
    } mouseButtons;

    struct vec2 mousePos;

private:

    float timer = 0.0f;
    float timerSpeed = 0.25f;

    struct {
        vk::Extent2D windowSize = { 1280, 720 };
        HINSTANCE windowInstance;
        HWND hwnd;

        std::unique_ptr<Camera> camera;

        std::unique_ptr<SwapChain> swapChain;
        std::unique_ptr<ImageViews> imageViews;
        std::unique_ptr<DescriptorSetLayout> descriptorSetLayout;
        std::unique_ptr<GraphicsPipeline> graphicsPipeline;
        std::unique_ptr<VertexBuffer> vertexBuffer;
        std::unique_ptr<UniformBuffers> uniformBuffers;
        std::unique_ptr<DescriptorPool> descriptorPool;
        std::unique_ptr<DescriptorSets> descriptorSets;
        std::unique_ptr<TextureImage> textureImage;
        std::unique_ptr<TextureImageView> textureImageView;
        std::unique_ptr<TextureSampler> textureSampler;
        std::unique_ptr<DepthResources> depthResources;
    } graphics;



    std::unique_ptr<Instance> instance;
    std::unique_ptr<DebugMessenger> debugMessenger;
    std::unique_ptr<Surface> surface;
    std::unique_ptr<Device> device;

    std::vector<Vertex> vertices;


    std::vector<std::pair<int, std::function<void()>>> keyVectorPress;
    std::vector<std::pair<int, std::function<void()>>> keyVectorRelease;
public:
    void setCameraType(Camera::CameraType type);
    void addVertice(Vertex &data);
    std::vector<Vertex> &getVertices();
    void addIndex(uint32_t indice);
    std::vector<uint32_t> &getIndices();

    void addKeyPress(int value, std::function<void()> &f);
    void addKeyRelease(int value, std::function<void()> &f);

    void move(glm::vec3 vector);

    HWND &getHwnd();

    HINSTANCE &getWindowInstance();

    void handleMouseMove(int32_t x, int32_t y);
    void handleMouseWheel(short );
    void handleKeyDown(uint32_t key);
    void handleKeyUp(uint32_t key);

private:
    glm::vec3 moveVector = glm::vec3(0);
    std::unique_ptr<Framebuffers> framebuffers;
    std::unique_ptr<CommandPool> commandPool;
    std::unique_ptr<CommandBuffers> commandBuffers;
    std::unique_ptr<Semaphore> semaphore;
    std::unique_ptr<Model> model;
    size_t currentFrame = 0;
    float frameTimer = 0;

    std::unordered_map<Vertex, uint32_t> uniqueVertices{};

    bool framebufferResized = false;


    HWND createWindow(HINSTANCE hinstance, WNDPROC wndproc);



    std::vector<uint32_t> indices = {
    };

private:
    void drawFrame();
    void updateUniformBuffer(uint32_t currentImage);

    void recreateSwapChain();

    void cleanupSwapChain();

    void cleanup();
};


#endif //INC_3DGAMEENGINECREATION_WINDOW_HPP
