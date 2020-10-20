cmake_minimum_required(VERSION 3.17)
project(3DGameEngineCreation)

set(CMAKE_CXX_STANDARD 17)

#set(Vulkan_LIBRARY "C:/Users/arthur/VulkanSDK/1.2.154.1/Lib")
#set(Vulkan_INCLUDE_DIR "C:/Users/arthur/VulkanSDK/1.2.154.1/Include")


set(SRC main.cpp
        Engine/Window/Window.cpp
        Engine/Window/Window.hpp
        Engine/Instance/Instance.cpp
        Engine/Instance/Instance.hpp
        Engine/Surface/Surface.cpp
        Engine/Surface/Surface.hpp
        Engine/Device/Device.cpp
        Engine/Device/Device.hpp
        Engine/QueueFamily/QueueFamily.cpp
        Engine/QueueFamily/QueueFamily.hpp
        Engine/SwapChain/SwapChain.cpp
        Engine/SwapChain/SwapChain.hpp
        Engine/ImageViews/ImageViews.cpp
        Engine/ImageViews/ImageViews.hpp
        Engine/GraphicsPipeline/GraphicsPipeline.cpp
        Engine/GraphicsPipeline/GraphicsPipeline.hpp
        Engine/FileReader/FileReader.cpp Engine/FileReader/FileReader.hpp Engine/Shader/Shader.cpp Engine/Shader/Shader.hpp Engine/Framebuffers/Framebuffers.cpp Engine/Framebuffers/Framebuffers.hpp Engine/CommandPool/CommandPool.cpp Engine/CommandPool/CommandPool.hpp Engine/CommandBuffers/CommandBuffers.cpp Engine/CommandBuffers/CommandBuffers.hpp Engine/Semaphore/Semaphore.cpp Engine/Semaphore/Semaphore.hpp Engine/Vertex/Vertex.cpp Engine/Vertex/Vertex.hpp Engine/VertexBuffer/VertexBuffer.cpp Engine/VertexBuffer/VertexBuffer.hpp Engine/DescriptorSetLayout/DescriptorSetLayout.cpp Engine/DescriptorSetLayout/DescriptorSetLayout.hpp Engine/UniformBuffers/UniformBuffers.cpp Engine/UniformBuffers/UniformBuffers.hpp Engine/DescriptorPool/DescriptorPool.cpp Engine/DescriptorPool/DescriptorPool.hpp Engine/DescriptorSets/DescriptorSets.cpp Engine/DescriptorSets/DescriptorSets.hpp Engine/DebugMessenger/DebugMessenger.cpp Engine/DebugMessenger/DebugMessenger.hpp Engine/TextureImage/TextureImage.cpp Engine/TextureImage/TextureImage.hpp Engine/TextureImageView/TextureImageView.cpp Engine/TextureImageView/TextureImageView.hpp Engine/TextureSampler/TextureSampler.cpp Engine/TextureSampler/TextureSampler.hpp Engine/DepthResources/DepthResources.cpp Engine/DepthResources/DepthResources.hpp)

add_executable(3DGameEngineCreation ${SRC})

include_directories(./stb-master/stb-master)

find_package(Vulkan REQUIRED)
add_subdirectory(./glfw-3.3.2)
add_subdirectory(./glm)


set(LIBS Vulkan::Vulkan glfw glm)
target_link_libraries(3DGameEngineCreation ${LIBS})