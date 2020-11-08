//
// Created by arthur on 17/10/2020.
//

#ifndef INC_3DGAMEENGINECREATION_DESCRIPTORSETS_HPP
#define INC_3DGAMEENGINECREATION_DESCRIPTORSETS_HPP

#include "../DescriptorSetLayout/DescriptorSetLayout.hpp"
#include "../ImageViews/ImageViews.hpp"
#include "../UniformBuffers/UniformBuffers.hpp"
#include "../DescriptorPool/DescriptorPool.hpp"
#include "../TextureSampler/TextureSampler.hpp"
#include "../TextureImageView/TextureImageView.hpp"

class Model;

class DescriptorSets
{
public:
    DescriptorSets(Device &device, ImageViews &imageViews, DescriptorSetLayout &descriptorSetLayout,
                   UniformBuffers &uniformBuffers, DescriptorPool &descriptorPool,
                   TextureImageView &textureImageView, TextureSampler &textureSampler);

public:
    std::vector<VkDescriptorSet> &getDescriptorSets();

private:
    std::vector<VkDescriptorSet> descriptorSets;
};


#endif //INC_3DGAMEENGINECREATION_DESCRIPTORSETS_HPP
