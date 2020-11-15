//
// Created by arthur on 10/10/2020.
//

#ifndef INC_3DGAMEENGINECREATION_COMMANDBUFFERS_HPP
#define INC_3DGAMEENGINECREATION_COMMANDBUFFERS_HPP

#include <vulkan/vulkan.hpp>
#include <vector>
#include "ImageViews.hpp"
#include "Device.hpp"
#include "CommandPool.hpp"
#include "Framebuffers.hpp"
#include "GraphicsPipeline.hpp"
#include "Vertex.hpp"
#include "VertexBuffer.hpp"
#include "DescriptorSets.hpp"
#include "DescriptorSetLayout.hpp"

class Window;
class Model;

class CommandBuffers
{
public:
    CommandBuffers(Window *window, ImageViews &imageViews, Device &device, CommandPool &commandPool, Framebuffers &framebuffers,
                   GraphicsPipeline &graphicsPipeline, VertexBuffer &vertexBuffer,
                   DescriptorSets &descriptorSets, DescriptorSetLayout &descriptorSetLayout);

    void release(Device &device, CommandPool &commandPool);

public:
    std::vector<VkCommandBuffer> &getCommandBuffers();

private:
    std::vector<VkCommandBuffer> commandBuffers;



};


#endif //INC_3DGAMEENGINECREATION_COMMANDBUFFERS_HPP
