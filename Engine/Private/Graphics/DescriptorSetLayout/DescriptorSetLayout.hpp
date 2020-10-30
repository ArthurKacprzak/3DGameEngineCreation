//
// Created by arthur on 17/10/2020.
//

#ifndef INC_3DGAMEENGINECREATION_DESCRIPTORSETLAYOUT_HPP
#define INC_3DGAMEENGINECREATION_DESCRIPTORSETLAYOUT_HPP

#include <vulkan/vulkan.hpp>

#include "../../Compute/Device/Device.hpp"

class DescriptorSetLayout
{
public:
    DescriptorSetLayout(Device &device);

    VkDescriptorSetLayout &getDescriptorSetLayout();

private:
    VkDescriptorSetLayout descriptorSetLayout;
};


#endif //INC_3DGAMEENGINECREATION_DESCRIPTORSETLAYOUT_HPP
