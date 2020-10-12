//
// Created by arthur on 10/10/2020.
//

#ifndef INC_3DGAMEENGINECREATION_COMMANDBUFFERS_HPP
#define INC_3DGAMEENGINECREATION_COMMANDBUFFERS_HPP

#include <vulkan/vulkan.hpp>
#include <vector>
#include "../ImageViews/ImageViews.hpp"
#include "../Device/Device.hpp"
#include "../CommandPool/CommandPool.hpp"
#include "../Framebuffers/Framebuffers.hpp"
#include "../GraphicsPipeline/GraphicsPipeline.hpp"

class CommandBuffers
{
public:
    CommandBuffers(ImageViews &imageViews, Device &device, CommandPool &commandPool, Framebuffers &framebuffers, GraphicsPipeline &graphicsPipeline);

public:
    std::vector<VkCommandBuffer> &getCommandBuffers();

private:
    std::vector<VkCommandBuffer> commandBuffers;
};


#endif //INC_3DGAMEENGINECREATION_COMMANDBUFFERS_HPP
