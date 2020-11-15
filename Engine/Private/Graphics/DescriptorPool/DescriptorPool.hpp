//
// Created by arthur on 17/10/2020.
//

#ifndef INC_3DGAMEENGINECREATION_DESCRIPTORPOOL_HPP
#define INC_3DGAMEENGINECREATION_DESCRIPTORPOOL_HPP

#include "Device.hpp"
#include "ImageViews.hpp"

class DescriptorPool
{
public:
    DescriptorPool(Device &device, ImageViews &imageViews);

    void release(Device &device);

public:
    VkDescriptorPool &getDescriptorPool();

private:
    VkDescriptorPool descriptorPool;
};


#endif //INC_3DGAMEENGINECREATION_DESCRIPTORPOOL_HPP
