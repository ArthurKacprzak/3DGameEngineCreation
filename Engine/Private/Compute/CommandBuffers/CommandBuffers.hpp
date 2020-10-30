//
// Created by arthur on 10/10/2020.
//

#ifndef INC_3DGAMEENGINECREATION_COMMANDBUFFERS_HPP
#define INC_3DGAMEENGINECREATION_COMMANDBUFFERS_HPP

#include <vulkan/vulkan.hpp>
#include <vector>
#include "../../Graphics/ImageViews/ImageViews.hpp"
#include "../Device/Device.hpp"
#include "../CommandPool/CommandPool.hpp"
#include "../../Graphics/Framebuffers/Framebuffers.hpp"
#include "../../Graphics/GraphicsPipeline/GraphicsPipeline.hpp"
#include "../../Graphics/Vertex/Vertex.hpp"
#include "../../Graphics/VertexBuffer/VertexBuffer.hpp"
#include "../../Graphics/DescriptorSets/DescriptorSets.hpp"
#include "../../Graphics/DescriptorSetLayout/DescriptorSetLayout.hpp"

class Window;

class CommandBuffers
{
public:
    CommandBuffers(Window *window, ImageViews &imageViews, Device &device, CommandPool &commandPool, Framebuffers &framebuffers,
                   GraphicsPipeline &graphicsPipeline, std::vector<Vertex> &vertices, VertexBuffer &vertexBuffer,
                   DescriptorSets &descriptorSets, DescriptorSetLayout &descriptorSetLayout);

public:
    std::vector<VkCommandBuffer> &getCommandBuffers();

private:
    std::vector<VkCommandBuffer> commandBuffers;
};


#endif //INC_3DGAMEENGINECREATION_COMMANDBUFFERS_HPP
