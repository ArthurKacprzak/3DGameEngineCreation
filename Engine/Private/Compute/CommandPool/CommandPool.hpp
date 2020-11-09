//
// Created by arthur on 10/10/2020.
//

#ifndef INC_3DGAMEENGINECREATION_COMMANDPOOL_HPP
#define INC_3DGAMEENGINECREATION_COMMANDPOOL_HPP

#include <vulkan/vulkan.hpp>
#include "../QueueFamily/QueueFamily.hpp"
#include "../Device/Device.hpp"
#include "../Surface/Surface.hpp"

class CommandPool
{
public:
    CommandPool(Device &device, Surface &surface);

    VkCommandPool &getCommandPool();

    void release(Device &device);

private:
    VkCommandPool commandPool;
};


#endif //INC_3DGAMEENGINECREATION_COMMANDPOOL_HPP
