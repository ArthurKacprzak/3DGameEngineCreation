//
// Created by arthur on 10/10/2020.
//

#ifndef INC_3DGAMEENGINECREATION_GRAPHICSPIPELINE_HPP
#define INC_3DGAMEENGINECREATION_GRAPHICSPIPELINE_HPP

#include "../../Compute/Device/Device.hpp"
#include "../ImageViews/ImageViews.hpp"
#include "../DescriptorSetLayout/DescriptorSetLayout.hpp"

class GraphicsPipeline
{
public:
    GraphicsPipeline(Device &device, ImageViews &imageViews, DescriptorSetLayout &descriptorSetLayout);

    void release(Device device);

private:
    VkPipelineLayout pipelineLayout;
    VkRenderPass renderPass;
    VkPipeline graphicsPipeline;

public:
    VkPipelineLayout &getPipelineLayout();

    VkPipeline &getGraphicsPipeline();

    VkRenderPass &getRenderPass();

private:
    void createRenderPass(Device &device, ImageViews &imageViews);
};


#endif //INC_3DGAMEENGINECREATION_GRAPHICSPIPELINE_HPP
