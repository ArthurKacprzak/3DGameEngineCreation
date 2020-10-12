//
// Created by arthur on 10/10/2020.
//

#include "Device.hpp"
#include "../QueueFamily/QueueFamily.hpp"
#include "../SwapChain/SwapChain.hpp"

Device::Device(Instance &instance, Surface &surface)
{
    this->deviceExtensions.push_back(VK_KHR_SWAPCHAIN_EXTENSION_NAME);
    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(instance.getVkInstance(), &deviceCount, nullptr);

    if (deviceCount == 0) {
        throw std::runtime_error("failed to find GPUs with Vulkan support!");
    }

    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(instance.getVkInstance(), &deviceCount, devices.data());

    for (const auto& d : devices) {
        if (isDeviceSuitable(d, surface)) {
            this->physicalDevice = d;
            break;
        }
    }

    if (physicalDevice == VK_NULL_HANDLE) {
        throw std::runtime_error("failed to find a suitable GPU!");
    }
    this->createLogicalDevice(surface);
}

bool Device::isDeviceSuitable(VkPhysicalDevice vkPhysicalDevice, Surface &surface)
{
    QueueFamily::QueueFamilyIndices indices = QueueFamily::findQueueFamilies(vkPhysicalDevice, surface);

    bool extensionsSupported = this->checkDeviceExtensionSupport(vkPhysicalDevice);

    bool swapChainAdequate = false;
    if (extensionsSupported) {
        SwapChain::SwapChainSupportDetails swapChainSupport = SwapChain::querySwapChainSupport(vkPhysicalDevice, surface);
        swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
    }

    return indices.isComplete() && extensionsSupported && swapChainAdequate;
}

bool Device::checkDeviceExtensionSupport(VkPhysicalDevice &vkPhysicalDevice) {
    uint32_t extensionCount;
    vkEnumerateDeviceExtensionProperties(vkPhysicalDevice, nullptr, &extensionCount, nullptr);

    std::vector<VkExtensionProperties> availableExtensions(extensionCount);
    vkEnumerateDeviceExtensionProperties(vkPhysicalDevice, nullptr, &extensionCount, availableExtensions.data());

    std::set<std::string> requiredExtensions(this->deviceExtensions.begin(), this->deviceExtensions.end());

    for (const auto& extension : availableExtensions) {
        requiredExtensions.erase(extension.extensionName);
    }

    return requiredExtensions.empty();
}

void Device::createLogicalDevice(Surface &surface) {
    QueueFamily::QueueFamilyIndices indices = QueueFamily::findQueueFamilies(this->physicalDevice, surface);

    std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
    std::set<uint32_t> uniqueQueueFamilies = {indices.graphicsFamily.value(), indices.presentFamily.value()};

    float queuePriority = 1.0f;
    for (uint32_t queueFamily : uniqueQueueFamilies) {
        VkDeviceQueueCreateInfo queueCreateInfo{};
        queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueCreateInfo.queueFamilyIndex = queueFamily;
        queueCreateInfo.queueCount = 1;
        queueCreateInfo.pQueuePriorities = &queuePriority;
        queueCreateInfos.push_back(queueCreateInfo);
    }

    VkPhysicalDeviceFeatures deviceFeatures{};

    VkDeviceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

    createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
    createInfo.pQueueCreateInfos = queueCreateInfos.data();

    createInfo.pEnabledFeatures = &deviceFeatures;

    createInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size());
    createInfo.ppEnabledExtensionNames = deviceExtensions.data();

    createInfo.enabledLayerCount = 0;

    if (vkCreateDevice(physicalDevice, &createInfo, nullptr, &this->device) != VK_SUCCESS) {
        throw std::runtime_error("failed to create logical device!");
    }

    vkGetDeviceQueue(this->device, indices.graphicsFamily.value(), 0, &this->graphicsQueue);
    vkGetDeviceQueue(this->device, indices.presentFamily.value(), 0, &this->presentQueue);
}

Device::~Device()
{

}

VkPhysicalDevice &Device::getPhysicalDevice()
{
    return this->physicalDevice;
}

VkDevice &Device::getDevice()
{
    return this->device;
}

VkQueue &Device::getGraphicsQueue()
{
    return graphicsQueue;
}

VkQueue &Device::getPresentQueue()
{
    return presentQueue;
}
