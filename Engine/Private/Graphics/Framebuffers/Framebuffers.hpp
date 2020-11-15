//
// Created by arthur on 10/10/2020.
//

#ifndef INC_3DGAMEENGINECREATION_FRAMEBUFFERS_HPP
#define INC_3DGAMEENGINECREATION_FRAMEBUFFERS_HPP

#include "ImageViews.hpp"
#include "Device.hpp"
#include "GraphicsPipeline.hpp"
#include "DepthResources.hpp"

class Framebuffers
{
public:
    Framebuffers(ImageViews &imageViews, Device &device, GraphicsPipeline &graphicsPipeline, DepthResources &depthResources);

    std::vector<VkFramebuffer> &getSwapChainFramebuffers();

    void release(Device &device);

private:
    std::vector<VkFramebuffer> swapChainFramebuffers;
};


#endif //INC_3DGAMEENGINECREATION_FRAMEBUFFERS_HPP
