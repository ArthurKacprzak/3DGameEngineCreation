cmake_minimum_required(VERSION 3.17)
project(3DGameEngineCreation)

set(CMAKE_CXX_STANDARD 17)

#set(Vulkan_LIBRARY "C:/Users/arthur/VulkanSDK/1.2.154.1/Lib")
#set(Vulkan_INCLUDE_DIR "C:/Users/arthur/VulkanSDK/1.2.154.1/Include")


set(SRC main.cpp
        Engine/Private/Window/Window.cpp
        Engine/Private/Window/Window.hpp
        Engine/Private/Compute/Instance/Instance.cpp
        Engine/Private/Compute/Instance/Instance.hpp
        Engine/Private/Compute/Surface/Surface.cpp
        Engine/Private/Compute/Surface/Surface.hpp
        Engine/Private/Compute/Device/Device.cpp
        Engine/Private/Compute/Device/Device.hpp
        Engine/Private/Compute/QueueFamily/QueueFamily.cpp
        Engine/Private/Compute/QueueFamily/QueueFamily.hpp
        Engine/Private/Graphics/SwapChain/SwapChain.cpp
        Engine/Private/Graphics/SwapChain/SwapChain.hpp
        Engine/Private/Graphics/ImageViews/ImageViews.cpp
        Engine/Private/Graphics/ImageViews/ImageViews.hpp
        Engine/Private/Graphics/GraphicsPipeline/GraphicsPipeline.cpp
        Engine/Private/Graphics/GraphicsPipeline/GraphicsPipeline.hpp
        Engine/Private/Compute/FileReader/FileReader.cpp
        Engine/Private/Compute/FileReader/FileReader.hpp
        Engine/Private/Graphics/Shader/Shader.cpp
        Engine/Private/Graphics/Shader/Shader.hpp
        Engine/Private/Graphics/Framebuffers/Framebuffers.cpp
        Engine/Private/Graphics/Framebuffers/Framebuffers.hpp
        Engine/Private/Compute/CommandPool/CommandPool.cpp
        Engine/Private/Compute/CommandPool/CommandPool.hpp
        Engine/Private/Compute/CommandBuffers/CommandBuffers.cpp
        Engine/Private/Compute/CommandBuffers/CommandBuffers.hpp
        Engine/Private/Compute/Semaphore/Semaphore.cpp
        Engine/Private/Compute/Semaphore/Semaphore.hpp
        Engine/Private/Graphics/Vertex/Vertex.cpp
        Engine/Private/Graphics/Vertex/Vertex.hpp
        Engine/Private/Graphics/VertexBuffer/VertexBuffer.cpp
        Engine/Private/Graphics/VertexBuffer/VertexBuffer.hpp
        Engine/Private/Graphics/DescriptorSetLayout/DescriptorSetLayout.cpp
        Engine/Private/Graphics/DescriptorSetLayout/DescriptorSetLayout.hpp
        Engine/Private/Graphics/UniformBuffers/UniformBuffers.cpp
        Engine/Private/Graphics/UniformBuffers/UniformBuffers.hpp
        Engine/Private/Graphics/DescriptorPool/DescriptorPool.cpp
        Engine/Private/Graphics/DescriptorPool/DescriptorPool.hpp
        Engine/Private/Graphics/DescriptorSets/DescriptorSets.cpp
        Engine/Private/Graphics/DescriptorSets/DescriptorSets.hpp
        Engine/Private/Compute/DebugMessenger/DebugMessenger.cpp
        Engine/Private/Compute/DebugMessenger/DebugMessenger.hpp
        Engine/Private/Graphics/TextureImage/TextureImage.cpp
        Engine/Private/Graphics/TextureImage/TextureImage.hpp
        Engine/Private/Graphics/TextureImageView/TextureImageView.cpp
        Engine/Private/Graphics/TextureImageView/TextureImageView.hpp
        Engine/Private/Graphics/TextureSampler/TextureSampler.cpp
        Engine/Private/Graphics/TextureSampler/TextureSampler.hpp
        Engine/Private/Graphics/DepthResources/DepthResources.cpp
        Engine/Private/Graphics/DepthResources/DepthResources.hpp
        Engine/Private/Graphics/Model/Model.cpp
        Engine/Private/Graphics/Model/Model.hpp
        Engine/Public/Application/Application.cpp
        Engine/Public/Application/Application.hpp
        Engine/Public/Object/Object.cpp
        Engine/Public/Object/Object.hpp
        Engine/Private/Compute/CommandPool/CommandPool.cpp
        Engine/Private/Compute/CommandPool/CommandPool.hpp
        Engine/Private/Compute/CommandBuffers/CommandBuffers.cpp
        Engine/Private/Compute/CommandBuffers/CommandBuffers.hpp
        Engine/Private/Compute/Semaphore/Semaphore.cpp
        Engine/Private/Compute/Semaphore/Semaphore.hpp
        Engine/Private/Graphics/Vertex/Vertex.cpp
        Engine/Private/Graphics/Vertex/Vertex.hpp
        Engine/Private/Graphics/VertexBuffer/VertexBuffer.cpp
        Engine/Private/Graphics/VertexBuffer/VertexBuffer.hpp
        Engine/Private/Graphics/DescriptorSetLayout/DescriptorSetLayout.cpp
        Engine/Private/Graphics/DescriptorSetLayout/DescriptorSetLayout.hpp
        Engine/Private/Graphics/UniformBuffers/UniformBuffers.cpp
        Engine/Private/Graphics/UniformBuffers/UniformBuffers.hpp
        Engine/Private/Graphics/DescriptorPool/DescriptorPool.cpp
        Engine/Private/Graphics/DescriptorPool/DescriptorPool.hpp
        Engine/Private/Graphics/DescriptorSets/DescriptorSets.cpp
        Engine/Private/Graphics/DescriptorSets/DescriptorSets.hpp
        Engine/Private/Compute/DebugMessenger/DebugMessenger.cpp
        Engine/Private/Compute/DebugMessenger/DebugMessenger.hpp
        Engine/Private/Graphics/TextureImage/TextureImage.cpp
        Engine/Private/Graphics/TextureImage/TextureImage.hpp
        Engine/Private/Graphics/TextureImageView/TextureImageView.cpp
        Engine/Private/Graphics/TextureImageView/TextureImageView.hpp
        Engine/Private/Graphics/TextureSampler/TextureSampler.cpp
        Engine/Private/Graphics/TextureSampler/TextureSampler.hpp
        Engine/Private/Graphics/DepthResources/DepthResources.cpp
        Engine/Private/Graphics/DepthResources/DepthResources.hpp
        Engine/Private/Graphics/Model/Model.cpp
        Engine/Private/Graphics/Model/Model.hpp
        ourLibs/miniobjloader/loader.cpp
        ourLibs/miniobjloader/loader.hpp
        ourLibs/miniobjloader/tools.cpp
        ourLibs/miniobjloader/tools.hpp
        Engine/Public/PublicModel/PublicModel.cpp
        Engine/Public/PublicModel/PublicModel.hpp
        Engine/Public/Texture/Texture.cpp
        Engine/Public/Texture/Texture.hpp Engine/Public/Key/Key.cpp Engine/Public/Key/Key.hpp Engine/Private/Graphics/Camera/Camera.cpp Engine/Private/Graphics/Camera/Camera.hpp Engine/Private/Tools/VkTools.cpp Engine/Private/Tools/VkTools.hpp Engine/Private/Physics/Maths/TriPhysics.cpp Engine/Private/Physics/Maths/TriPhysics.hpp)


add_executable(3DGameEngineCreation ${SRC})

include_directories(./stb-master/stb-master)

find_package(Vulkan REQUIRED)
add_subdirectory(./glm)


set(LIBS Vulkan::Vulkan glm )
target_link_libraries(3DGameEngineCreation ${LIBS})