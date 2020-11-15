//
// Created by arthur on 17/10/2020.
//

#ifndef INC_3DGAMEENGINECREATION_DESCRIPTORSETLAYOUT_HPP
#define INC_3DGAMEENGINECREATION_DESCRIPTORSETLAYOUT_HPP

#include <vulkan/vulkan.hpp>

#include "Device.hpp"

class DescriptorSetLayout
{
public:
    DescriptorSetLayout(Device &device);

    VkDescriptorSetLayout &getDescriptorSetLayout();

    void release(Device &device);

private:
    VkDescriptorSetLayout descriptorSetLayout;
};


#endif //INC_3DGAMEENGINECREATION_DESCRIPTORSETLAYOUT_HPP
