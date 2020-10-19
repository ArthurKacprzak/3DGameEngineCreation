//
// Created by arthur on 19/10/2020.
//

#ifndef INC_3DGAMEENGINECREATION_TEXTUREIMAGEVIEW_HPP
#define INC_3DGAMEENGINECREATION_TEXTUREIMAGEVIEW_HPP

#include "../TextureImage/TextureImage.hpp"

class TextureImageView
{
public:
    TextureImageView(Device &device, TextureImage &textureImage);

private:
    VkImageView createImageView(Device &device, TextureImage &textureImage, VkFormat format);

public:
    VkImageView &getTextureImageView();

private:
    VkImageView textureImageView;
};


#endif //INC_3DGAMEENGINECREATION_TEXTUREIMAGEVIEW_HPP
