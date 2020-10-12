//
// Created by arthur on 10/10/2020.
//

#ifndef INC_3DGAMEENGINECREATION_GRAPHICSPIPELINE_HPP
#define INC_3DGAMEENGINECREATION_GRAPHICSPIPELINE_HPP

#include "../Device/Device.hpp"
#include "../ImageViews/ImageViews.hpp"

class GraphicsPipeline
{
public:
    GraphicsPipeline(Device &device, ImageViews &imageViews);

private:
    VkPipelineLayout pipelineLayout;
    VkRenderPass renderPass;
    VkPipeline graphicsPipeline;
public:
    VkPipeline &getGraphicsPipeline();

    VkRenderPass &getRenderPass();

private:
    void createRenderPass(Device &device, ImageViews &imageViews);
};


#endif //INC_3DGAMEENGINECREATION_GRAPHICSPIPELINE_HPP
