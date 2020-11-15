//
// Created by arthur on 19/10/2020.
//

#ifndef INC_3DGAMEENGINECREATION_TEXTUREIMAGEVIEW_HPP
#define INC_3DGAMEENGINECREATION_TEXTUREIMAGEVIEW_HPP

#include "TextureImage.hpp"

class TextureImageView
{
public:
    TextureImageView(Device &device, TextureImage &textureImage);

    void release(Device &device);

public:
    static VkImageView createImageView(Device &device, VkImage &image, VkFormat format, VkImageAspectFlags aspectFlags);

public:
    VkImageView &getTextureImageView();

private:
    VkImageView textureImageView;
};


#endif //INC_3DGAMEENGINECREATION_TEXTUREIMAGEVIEW_HPP
