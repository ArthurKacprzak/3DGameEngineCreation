//
// Created by arthur on 10/10/2020.
//

#include "Framebuffers.hpp"

Framebuffers::Framebuffers(ImageViews &imageViews, Device &device, GraphicsPipeline &graphicsPipeline)
{
    this->swapChainFramebuffers.resize(imageViews.getSwapChainImageViews().size());

    for (size_t i = 0; i < imageViews.getSwapChainImageViews().size(); i++) {
        VkImageView attachments[] = {
                imageViews.getSwapChainImageViews()[i]
        };

        VkFramebufferCreateInfo framebufferInfo{};
        framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        framebufferInfo.renderPass = graphicsPipeline.getRenderPass();
        framebufferInfo.attachmentCount = 1;
        framebufferInfo.pAttachments = attachments;
        framebufferInfo.width = imageViews.getSwapChainExtent().width;
        framebufferInfo.height = imageViews.getSwapChainExtent().height;
        framebufferInfo.layers = 1;

        if (vkCreateFramebuffer(device.getDevice(), &framebufferInfo, nullptr, &swapChainFramebuffers[i]) != VK_SUCCESS) {
            throw std::runtime_error("échec de la création d'un framebuffer!");
        }
    }
}

std::vector<VkFramebuffer> &Framebuffers::getSwapChainFramebuffers()
{
    return swapChainFramebuffers;
}
