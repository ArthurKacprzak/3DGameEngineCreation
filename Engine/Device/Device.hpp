//
// Created by arthur on 10/10/2020.
//

#ifndef INC_3DGAMEENGINECREATION_DEVICE_HPP
#define INC_3DGAMEENGINECREATION_DEVICE_HPP

#include "../Instance/Instance.hpp"

#include <set>
#include <iostream>
#include <vector>
#include <cstdlib>

class Device
{
public:
    Device(Instance &instance, Surface &surface);
    ~Device();

public:
    VkPhysicalDevice &getPhysicalDevice();
    VkDevice &getDevice();
    VkQueue &getGraphicsQueue();
    VkQueue &getPresentQueue();

private:
    VkPhysicalDevice physicalDevice;
    VkDevice device;

    std::vector<const char*> deviceExtensions;

private:
    VkQueue graphicsQueue;
    VkQueue presentQueue;

private:
    bool isDeviceSuitable(VkPhysicalDevice vkPhysicalDevice, Surface &surface);
    bool checkDeviceExtensionSupport(VkPhysicalDevice &vkPhysicalDevice);
    void createLogicalDevice(Surface &surface);
};


#endif //INC_3DGAMEENGINECREATION_DEVICE_HPP
