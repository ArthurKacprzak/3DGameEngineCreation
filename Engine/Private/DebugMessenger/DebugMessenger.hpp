//
// Created by arthur on 17/10/2020.
//

#ifndef INC_3DGAMEENGINECREATION_DEBUGMESSENGER_HPP
#define INC_3DGAMEENGINECREATION_DEBUGMESSENGER_HPP

#include <vulkan/vulkan.hpp>

#include "../Instance/Instance.hpp"

class DebugMessenger
{
public:
    DebugMessenger(Instance &instance);
    void release(Instance &instance, const VkAllocationCallbacks* pAllocator);

public:
    static void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);
    static bool checkValidationLayerSupport();
public:
    const static bool ENABLEVALIDATIONLAYERS = true;

private:
    VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);

        private:
    VkDebugUtilsMessengerEXT debugMessenger;

public:

    static std::vector<const char*> &getValidationLayers();

    VkDebugUtilsMessengerEXT &getDebugMessenger();
};


#endif //INC_3DGAMEENGINECREATION_DEBUGMESSENGER_HPP
