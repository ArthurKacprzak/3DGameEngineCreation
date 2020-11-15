//
// Created by arthur on 10/10/2020.
//

#ifndef INC_3DGAMEENGINECREATION_QUEUEFAMILY_HPP
#define INC_3DGAMEENGINECREATION_QUEUEFAMILY_HPP

#include <optional>
#include <vulkan/vulkan.h>
#include <vector>
#include "Surface.hpp"

class QueueFamily
{
public:
    struct QueueFamilyIndices {
        std::optional<uint32_t> graphicsFamily;
        std::optional<uint32_t> presentFamily;

        bool isComplete() const {
            return graphicsFamily.has_value() && presentFamily.has_value();
        }
    };

public:
    static QueueFamilyIndices findQueueFamilies(VkPhysicalDevice &device, Surface &surface);
};


#endif //INC_3DGAMEENGINECREATION_QUEUEFAMILY_HPP
