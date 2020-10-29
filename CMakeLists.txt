cmake_minimum_required(VERSION 3.17)
project(3DGameEngineCreation)

set(CMAKE_CXX_STANDARD 17)

#set(Vulkan_LIBRARY "C:/Users/arthur/VulkanSDK/1.2.154.1/Lib")
#set(Vulkan_INCLUDE_DIR "C:/Users/arthur/VulkanSDK/1.2.154.1/Include")


set(SRC main.cpp
        Engine/Private/Window/Window.cpp
        Engine/Private/Window/Window.hpp
        Engine/Private/Instance/Instance.cpp
        Engine/Private/Instance/Instance.hpp
        Engine/Private/Surface/Surface.cpp
        Engine/Private/Surface/Surface.hpp
        Engine/Private/Device/Device.cpp
        Engine/Private/Device/Device.hpp
        Engine/Private/QueueFamily/QueueFamily.cpp
        Engine/Private/QueueFamily/QueueFamily.hpp
        Engine/Private/SwapChain/SwapChain.cpp
        Engine/Private/SwapChain/SwapChain.hpp
        Engine/Private/ImageViews/ImageViews.cpp
        Engine/Private/ImageViews/ImageViews.hpp
        Engine/Private/GraphicsPipeline/GraphicsPipeline.cpp
        Engine/Private/GraphicsPipeline/GraphicsPipeline.hpp
        Engine/Private/FileReader/FileReader.cpp
        Engine/Private/FileReader/FileReader.hpp
        Engine/Private/Shader/Shader.cpp
        Engine/Private/Shader/Shader.hpp
        Engine/Private/Framebuffers/Framebuffers.cpp
        Engine/Private/Framebuffers/Framebuffers.hpp
        Engine/Private/CommandPool/CommandPool.cpp
        Engine/Private/CommandPool/CommandPool.hpp
        Engine/Private/CommandBuffers/CommandBuffers.cpp
        Engine/Private/CommandBuffers/CommandBuffers.hpp
        Engine/Private/Semaphore/Semaphore.cpp
        Engine/Private/Semaphore/Semaphore.hpp
        Engine/Private/Vertex/Vertex.cpp
        Engine/Private/Vertex/Vertex.hpp
        Engine/Private/VertexBuffer/VertexBuffer.cpp
        Engine/Private/VertexBuffer/VertexBuffer.hpp
        Engine/Private/DescriptorSetLayout/DescriptorSetLayout.cpp
        Engine/Private/DescriptorSetLayout/DescriptorSetLayout.hpp
        Engine/Private/UniformBuffers/UniformBuffers.cpp
        Engine/Private/UniformBuffers/UniformBuffers.hpp
        Engine/Private/DescriptorPool/DescriptorPool.cpp
        Engine/Private/DescriptorPool/DescriptorPool.hpp
        Engine/Private/DescriptorSets/DescriptorSets.cpp
        Engine/Private/DescriptorSets/DescriptorSets.hpp
        Engine/Private/DebugMessenger/DebugMessenger.cpp
        Engine/Private/DebugMessenger/DebugMessenger.hpp
        Engine/Private/TextureImage/TextureImage.cpp
        Engine/Private/TextureImage/TextureImage.hpp
        Engine/Private/TextureImageView/TextureImageView.cpp
        Engine/Private/TextureImageView/TextureImageView.hpp
        Engine/Private/TextureSampler/TextureSampler.cpp
        Engine/Private/TextureSampler/TextureSampler.hpp
        Engine/Private/DepthResources/DepthResources.cpp
        Engine/Private/DepthResources/DepthResources.hpp
        Engine/Private/Model/Model.cpp
        Engine/Private/Model/Model.hpp
        Engine/Public/Rect/Rect.cpp
        Engine/Public/Rect/Rect.hpp
        Engine/Public/Application/Application.cpp
        Engine/Public/Application/Application.hpp
        Engine/Public/Object/Object.cpp
        Engine/Public/Object/Object.hpp
        Engine/Private/CommandPool/CommandPool.cpp Engine/Private/CommandPool/CommandPool.hpp Engine/Private/CommandBuffers/CommandBuffers.cpp Engine/Private/CommandBuffers/CommandBuffers.hpp Engine/Private/Semaphore/Semaphore.cpp Engine/Private/Semaphore/Semaphore.hpp Engine/Private/Vertex/Vertex.cpp Engine/Private/Vertex/Vertex.hpp Engine/Private/VertexBuffer/VertexBuffer.cpp Engine/Private/VertexBuffer/VertexBuffer.hpp Engine/Private/DescriptorSetLayout/DescriptorSetLayout.cpp Engine/Private/DescriptorSetLayout/DescriptorSetLayout.hpp Engine/Private/UniformBuffers/UniformBuffers.cpp Engine/Private/UniformBuffers/UniformBuffers.hpp Engine/Private/DescriptorPool/DescriptorPool.cpp Engine/Private/DescriptorPool/DescriptorPool.hpp Engine/Private/DescriptorSets/DescriptorSets.cpp Engine/Private/DescriptorSets/DescriptorSets.hpp Engine/Private/DebugMessenger/DebugMessenger.cpp Engine/Private/DebugMessenger/DebugMessenger.hpp Engine/Private/TextureImage/TextureImage.cpp Engine/Private/TextureImage/TextureImage.hpp Engine/Private/TextureImageView/TextureImageView.cpp Engine/Private/TextureImageView/TextureImageView.hpp Engine/Private/TextureSampler/TextureSampler.cpp Engine/Private/TextureSampler/TextureSampler.hpp Engine/Private/DepthResources/DepthResources.cpp Engine/Private/DepthResources/DepthResources.hpp Engine/Private/Model/Model.cpp Engine/Private/Model/Model.hpp ourLibs/miniobjloader/loader.cpp ourLibs/miniobjloader/loader.hpp ourLibs/miniobjloader/tools.cpp ourLibs/miniobjloader/tools.hpp)

add_executable(3DGameEngineCreation ${SRC})

include_directories(./stb-master/stb-master)

find_package(Vulkan REQUIRED)
add_subdirectory(./glfw-3.3.2)
add_subdirectory(./glm)
add_subdirectory(./tinyobjloader)


set(LIBS Vulkan::Vulkan glfw glm tinyobjloader)
target_link_libraries(3DGameEngineCreation ${LIBS})