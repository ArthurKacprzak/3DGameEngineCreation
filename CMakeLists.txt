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
        Engine/QueueFamily/QueueFamily.hpp Engine/SwapChain/SwapChain.cpp Engine/SwapChain/SwapChain.hpp Engine/ImageViews/ImageViews.cpp Engine/ImageViews/ImageViews.hpp Engine/GraphicsPipeline/GraphicsPipeline.cpp Engine/GraphicsPipeline/GraphicsPipeline.hpp Engine/FileReader/FileReader.cpp Engine/FileReader/FileReader.hpp Engine/Shader/Shader.cpp Engine/Shader/Shader.hpp Engine/Framebuffers/Framebuffers.cpp Engine/Framebuffers/Framebuffers.hpp Engine/CommandPool/CommandPool.cpp Engine/CommandPool/CommandPool.hpp Engine/CommandBuffers/CommandBuffers.cpp Engine/CommandBuffers/CommandBuffers.hpp Engine/Semaphore/Semaphore.cpp Engine/Semaphore/Semaphore.hpp)

add_executable(3DGameEngineCreation ${SRC})

find_package(Vulkan REQUIRED)
add_subdirectory(./glfw-3.3.2)
add_subdirectory(./glm)


set(LIBS Vulkan::Vulkan glfw glm)
target_link_libraries(3DGameEngineCreation ${LIBS})