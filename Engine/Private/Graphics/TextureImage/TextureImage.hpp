//
// Created by arthur on 18/10/2020.
//

#ifndef INC_3DGAMEENGINECREATION_TEXTUREIMAGE_HPP
#define INC_3DGAMEENGINECREATION_TEXTUREIMAGE_HPP

#include "../../Compute/Device/Device.hpp"
#include "../VertexBuffer/VertexBuffer.hpp"
#include "../../Compute/CommandPool/CommandPool.hpp"

class TextureImage
{
public:
    TextureImage(Device &device, CommandPool &commandPool);

public:
    VkImage &getTextureImage();

    VkDeviceMemory &getTextureImageMemory();

public:

    static void createImage(Device &device, uint32_t width, uint32_t height, VkFormat format,
                            VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties,
                            VkImage& image, VkDeviceMemory& imageMemory);

private:
    void transitionImageLayout(Device &device, CommandPool &commandPool, VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);
    void copyBufferToImage(Device &device, CommandPool &commandPool, VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);
    VkCommandBuffer beginSingleTimeCommands(Device &device, CommandPool &commandPool);
    void endSingleTimeCommands(Device &device, CommandPool &commandPool, VkCommandBuffer commandBuffer);


private:
    VkImage textureImage;
    VkDeviceMemory textureImageMemory;
};


#endif //INC_3DGAMEENGINECREATION_TEXTUREIMAGE_HPP
