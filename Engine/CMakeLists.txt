cmake_minimum_required(VERSION 3.17)
project(Engine)

set(CMAKE_CXX_STANDARD 17)
set(Main main.cpp)

set(SRC Private/Window/Window.cpp
        Private/Compute/Instance/Instance.cpp
        Private/Compute/Surface/Surface.cpp
        Private/Compute/Device/Device.cpp
        Private/Compute/QueueFamily/QueueFamily.cpp
        Private/Graphics/SwapChain/SwapChain.cpp
        Private/Graphics/ImageViews/ImageViews.cpp
        Private/Graphics/GraphicsPipeline/GraphicsPipeline.cpp
        Private/Compute/FileReader/FileReader.cpp
        Private/Graphics/Shader/Shader.cpp
        Private/Graphics/Framebuffers/Framebuffers.cpp
        Private/Compute/CommandPool/CommandPool.cpp
        Private/Compute/CommandBuffers/CommandBuffers.cpp
        Private/Compute/Semaphore/Semaphore.cpp
        Private/Graphics/Vertex/Vertex.cpp
        Private/Graphics/VertexBuffer/VertexBuffer.cpp
        Private/Graphics/DescriptorSetLayout/DescriptorSetLayout.cpp
        Private/Graphics/UniformBuffers/UniformBuffers.cpp
        Private/Graphics/DescriptorPool/DescriptorPool.cpp
        Private/Graphics/DescriptorSets/DescriptorSets.cpp
        Private/Compute/DebugMessenger/DebugMessenger.cpp
        Private/Graphics/TextureImage/TextureImage.cpp
        Private/Graphics/TextureImageView/TextureImageView.cpp
        Private/Graphics/TextureSampler/TextureSampler.cpp
        Private/Graphics/DepthResources/DepthResources.cpp
        Private/Graphics/Model/Model.cpp
        Public/Application/Application.cpp
        Public/Object/Object.cpp
        Private/Compute/CommandPool/CommandPool.cpp
        Private/Compute/CommandBuffers/CommandBuffers.cpp
        Private/Compute/Semaphore/Semaphore.cpp
        Private/Graphics/Vertex/Vertex.cpp
        Private/Graphics/VertexBuffer/VertexBuffer.cpp
        Private/Graphics/DescriptorSetLayout/DescriptorSetLayout.cpp
        Private/Graphics/UniformBuffers/UniformBuffers.cpp
        Private/Graphics/DescriptorPool/DescriptorPool.cpp
        Private/Graphics/DescriptorSets/DescriptorSets.cpp
        Private/Compute/DebugMessenger/DebugMessenger.cpp
        Private/Graphics/TextureImage/TextureImage.cpp
        Private/Graphics/TextureImageView/TextureImageView.cpp
        Private/Graphics/TextureSampler/TextureSampler.cpp
        Private/Graphics/DepthResources/DepthResources.cpp
        Private/Graphics/Model/Model.cpp
        ourLibs/miniobjloader/loader.cpp
        ourLibs/miniobjloader/tools.cpp
        Public/PublicModel/PublicModel.cpp
        Public/Texture/Texture.cpp
        Public/Key/Key.cpp
        Private/Graphics/Camera/Camera.cpp
        Private/Tools/VkTools.cpp
        Private/Physics/Maths/Math.cpp)

OPTION (BUILD_SHARED_LIBS "Build Shared Libraries" OFF)

include_directories(./stb-master/stb-master)
find_package(Vulkan REQUIRED)
set(LIBS Vulkan::Vulkan)


add_library(Engine STATIC ${SRC})
target_link_libraries(Engine ${LIBS})

set(HEAD_FILE Private/Window
        Private/Compute/Instance
        Private/Compute/Surface
        Private/Compute/Device
        Private/Compute/QueueFamily
        Private/Graphics/SwapChain
        Private/Graphics/ImageViews
        Private/Graphics/GraphicsPipeline
        Private/Compute/FileReader
        Private/Graphics/Shader
        Private/Graphics/Framebuffers
        Private/Compute/CommandPool
        Private/Compute/CommandBuffers
        Private/Compute/Semaphore
        Private/Graphics/Vertex
        Private/Graphics/VertexBuffer
        Private/Graphics/DescriptorSetLayout
        Private/Graphics/UniformBuffers
        Private/Graphics/DescriptorPool
        Private/Graphics/DescriptorSets
        Private/Compute/DebugMessenger
        Private/Graphics/TextureImage
        Private/Graphics/TextureImageView
        Private/Graphics/TextureSampler
        Private/Graphics/DepthResources
        Private/Graphics/Model
        Public/Application
        Public/Object
        Private/Compute/CommandPool
        Private/Compute/CommandBuffers
        Private/Compute/Semaphore
        Private/Graphics/Vertex
        Private/Graphics/VertexBuffer
        Private/Graphics/DescriptorSetLayout
        Private/Graphics/UniformBuffers
        Private/Graphics/DescriptorPool
        Private/Graphics/DescriptorSets
        Private/Compute/DebugMessenger
        Private/Graphics/TextureImage
        Private/Graphics/TextureImageView
        Private/Graphics/TextureSampler
        Private/Graphics/DepthResources
        Private/Graphics/Model
        ourLibs/miniobjloader
        ourLibs/miniobjloader
        Public/PublicModel
        Public/Texture
        Public/Key
        Private/Graphics/Camera
        Private/Tools
        Private/Physics/Maths)

target_include_directories (Engine PUBLIC ${HEAD_FILE})
