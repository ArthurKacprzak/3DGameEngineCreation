//
// Created by arthur on 10/10/2020.
//

#include "Instance.hpp"
#include "../DebugMessenger/DebugMessenger.hpp"
#include <windows.h>
#include <vulkan/vulkan_win32.h>

Instance::Instance()
{
    if (DebugMessenger::ENABLEVALIDATIONLAYERS && !DebugMessenger::checkValidationLayerSupport()) {
        throw std::runtime_error("validation layers requested, but not available!");
    }


    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Hello Triangle";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;

    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    auto extensions = this->getRequiredExtensions();
    createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
    createInfo.ppEnabledExtensionNames = extensions.data();

    VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo;
    if (DebugMessenger::ENABLEVALIDATIONLAYERS) {
        createInfo.enabledLayerCount = static_cast<uint32_t>(DebugMessenger::getValidationLayers().size());
        createInfo.ppEnabledLayerNames = DebugMessenger::getValidationLayers().data();

        DebugMessenger::populateDebugMessengerCreateInfo(debugCreateInfo);
        createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*) &debugCreateInfo;
    } else {
        createInfo.enabledLayerCount = 0;

        createInfo.pNext = nullptr;
    }

    if (vkCreateInstance(&createInfo, nullptr, &this->instance) != VK_SUCCESS) {
        throw std::runtime_error("failed to create instance!");
    }
}

std::vector<const char *> Instance::getRequiredExtensions()
{

    std::vector<const char*> enabledExtensions = { VK_KHR_SURFACE_EXTENSION_NAME, VK_KHR_WIN32_SURFACE_EXTENSION_NAME };


    enabledExtensions.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);
    enabledExtensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

    return enabledExtensions;
}

Instance::~Instance()
{
    vkDestroyInstance(this->instance, nullptr);
}

VkInstance Instance::getVkInstance()
{
    return this->instance;
}

