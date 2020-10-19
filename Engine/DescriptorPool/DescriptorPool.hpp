//
// Created by arthur on 17/10/2020.
//

#ifndef INC_3DGAMEENGINECREATION_DESCRIPTORPOOL_HPP
#define INC_3DGAMEENGINECREATION_DESCRIPTORPOOL_HPP

#include "../Device/Device.hpp"
#include "../ImageViews/ImageViews.hpp"

class DescriptorPool
{
public:
    DescriptorPool(Device &device, ImageViews &imageViews);

public:
    VkDescriptorPool &getDescriptorPool();

private:
    VkDescriptorPool descriptorPool;
};


#endif //INC_3DGAMEENGINECREATION_DESCRIPTORPOOL_HPP
