//
// Created by arthur on 10/10/2020.
//

#ifndef INC_3DGAMEENGINECREATION_FRAMEBUFFERS_HPP
#define INC_3DGAMEENGINECREATION_FRAMEBUFFERS_HPP

#include "../ImageViews/ImageViews.hpp"
#include "../Device/Device.hpp"
#include "../GraphicsPipeline/GraphicsPipeline.hpp"

class Framebuffers
{
public:
    Framebuffers(ImageViews &imageViews, Device &device, GraphicsPipeline &graphicsPipeline);

    std::vector<VkFramebuffer> &getSwapChainFramebuffers();

private:
    std::vector<VkFramebuffer> swapChainFramebuffers;
};


#endif //INC_3DGAMEENGINECREATION_FRAMEBUFFERS_HPP
