//
// Created by arthur on 09/10/2020.
//

#ifndef INC_3DGAMEENGINECREATION_WINDOW_HPP
#define INC_3DGAMEENGINECREATION_WINDOW_HPP

#include <vulkan/vulkan.h>
//#include <GLFW/glfw3.h>
#include <windows.h>
#include <stdexcept>
#include <cstdlib>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <chrono>

#include "../Compute/Surface/Surface.hpp"
#include "../Compute/Device/Device.hpp"
#include "../Compute/CommandPool/CommandPool.hpp"
#include "../Compute/CommandBuffers/CommandBuffers.hpp"
#include "../Compute/Semaphore/Semaphore.hpp"
#include "../Compute/DebugMessenger/DebugMessenger.hpp"

#include "../Graphics/SwapChain/SwapChain.hpp"
#include "../Graphics/ImageViews/ImageViews.hpp"
#include "../Graphics/GraphicsPipeline/GraphicsPipeline.hpp"
#include "../Graphics/DescriptorSetLayout/DescriptorSetLayout.hpp"
#include "../Graphics/DescriptorSets/DescriptorSets.hpp"
#include "../Graphics/Framebuffers/Framebuffers.hpp"
#include "../Graphics/Vertex/Vertex.hpp"
#include "../Graphics/VertexBuffer/VertexBuffer.hpp"
#include "../Graphics/UniformBuffers/UniformBuffers.hpp"
#include "../Graphics/DescriptorPool/DescriptorPool.hpp"
#include "../Graphics/TextureImage/TextureImage.hpp"
#include "../Graphics/TextureImageView/TextureImageView.hpp"
#include "../Graphics/TextureSampler/TextureSampler.hpp"
#include "../Graphics/DepthResources/DepthResources.hpp"

#include "../Graphics/Camera/Camera.hpp"

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

    glm::vec2 mousePos;

private:

    float timer = 0.0f;
    float timerSpeed = 0.25f;

    struct {
        vk::Extent2D windowSize = { 1280, 720 };
        HINSTANCE windowInstance;
        HWND hwnd;

        Camera *camera;

        SwapChain *swapChain;
        ImageViews *imageViews;
        DescriptorSetLayout *descriptorSetLayout;
        GraphicsPipeline *graphicsPipeline;
        VertexBuffer *vertexBuffer;
        UniformBuffers *uniformBuffers;
        DescriptorPool *descriptorPool;
        DescriptorSets *descriptorSets;
        TextureImage *textureImage;
        TextureImageView *textureImageView;
        TextureSampler *textureSampler;
        DepthResources *depthResources;
    } graphics;



    Instance *instance;
    DebugMessenger *debugMessenger;
    Surface *surface;
    Device *device;

    std::vector<Vertex> vertices;


    std::vector<std::pair<int, std::function<void()>>> keyVector;
public:
    void addVertice(Vertex &data);
    std::vector<Vertex> &getVertices();
    void addIndex(uint32_t indice);
    std::vector<uint32_t> &getIndices();

    void addKey(int value, std::function<void()> &f);


    HWND &getHwnd();

    HINSTANCE &getWindowInstance();

    void handleMouseMove(int32_t x, int32_t y);
    void handleMouseWheel(short );
    void handleKeyDown(uint32_t key);
    void handleKeyUp(uint32_t key);

private:
    Framebuffers *framebuffers;
    CommandPool *commandPool;
    CommandBuffers *commandBuffers;
    Semaphore *semaphore;
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
    void keyManagement();

    void recreateSwapChain();

    void cleanupSwapChain();

    void cleanup();
};


#endif //INC_3DGAMEENGINECREATION_WINDOW_HPP
