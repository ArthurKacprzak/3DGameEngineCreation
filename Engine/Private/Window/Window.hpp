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

#include "../Surface/Surface.hpp"
#include "../Device/Device.hpp"
#include "../SwapChain/SwapChain.hpp"
#include "../ImageViews/ImageViews.hpp"
#include "../GraphicsPipeline/GraphicsPipeline.hpp"
#include "../Framebuffers/Framebuffers.hpp"
#include "../CommandPool/CommandPool.hpp"
#include "../CommandBuffers/CommandBuffers.hpp"
#include "../Semaphore/Semaphore.hpp"
#include "../Vertex/Vertex.hpp"
#include "../VertexBuffer/VertexBuffer.hpp"
#include "../DescriptorSetLayout/DescriptorSetLayout.hpp"
#include "../UniformBuffers/UniformBuffers.hpp"
#include "../DescriptorPool/DescriptorPool.hpp"
#include "../DescriptorSets/DescriptorSets.hpp"
#include "../DebugMessenger/DebugMessenger.hpp"
#include "../TextureImage/TextureImage.hpp"
#include "../TextureImageView/TextureImageView.hpp"
#include "../TextureSampler/TextureSampler.hpp"
#include "../DepthResources/DepthResources.hpp"

class Model;

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
    void init(HINSTANCE hInstance);

private:
    vk::Extent2D windowSize = { 1280, 720 };
    HINSTANCE windowInstance;
    HWND hwnd;

    Instance *instance;
    DebugMessenger *debugMessenger;
    Surface *surface;
    Device *device;
    SwapChain *swapChain;
    ImageViews *imageViews;
    DescriptorSetLayout *descriptorSetLayout;
    GraphicsPipeline *graphicsPipeline;

    std::vector<Vertex> vertices;

    VertexBuffer *vertexBuffer;
    UniformBuffers *uniformBuffers;
    DescriptorPool *descriptorPool;
    DescriptorSets *descriptorSets;
    TextureImage *textureImage;
    TextureImageView *textureImageView;
    TextureSampler *textureSampler;

    DepthResources *depthResources;

    Model *model;

    std::vector<std::pair<int, std::function<void()>>> keyVector;
public:
    void addVertice(Vertex &data);
    std::vector<Vertex> &getVertices();
    void addIndex(uint32_t indice);
    std::vector<uint32_t> &getIndices();

    void addKey(int value, std::function<void()> &f);


    HWND &getHwnd();

    HINSTANCE &getWindowInstance();

private:
    Framebuffers *framebuffers;
    CommandPool *commandPool;
    CommandBuffers *commandBuffers;
    Semaphore *semaphore;
    size_t currentFrame = 0;

    std::unordered_map<Vertex, uint32_t> uniqueVertices{};

    bool framebufferResized = false;


    HWND createWindow(HINSTANCE hinstance, WNDPROC wndproc);

    static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        switch (uMsg)
        {
            case WM_CLOSE:
                DestroyWindow(hWnd);
                PostQuitMessage(0);
                break;
        }

        return (DefWindowProc(hWnd, uMsg, wParam, lParam));
    }



    std::vector<uint32_t> indices = {
/*                0, 1, 2, 2, 3, 0,
                4, 5, 6, 6, 7, 4,
                8, 9, 10, 10, 11, 8*/
    };

private:
    void drawFrame();
    void cleanupSwapChain();
    void recreateSwapChain();
    void updateUniformBuffer(uint32_t currentImage);
    void keyManagement();
    void cleanup();
};


#endif //INC_3DGAMEENGINECREATION_WINDOW_HPP
