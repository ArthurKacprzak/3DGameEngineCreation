//
// Created by arthur on 10/10/2020.
//

#ifndef INC_3DGAMEENGINECREATION_SEMAPHORE_HPP
#define INC_3DGAMEENGINECREATION_SEMAPHORE_HPP

#include <vulkan/vulkan.hpp>
#include "../../Graphics/ImageViews/ImageViews.hpp"
#include "../Device/Device.hpp"

class Semaphore
{
public:
    Semaphore(ImageViews &imageViews, Device &device);

public:
    std::vector<VkSemaphore> &getImageAvailableSemaphores();
    std::vector<VkSemaphore> &getRenderFinishedSemaphores();
    std::vector<VkFence> &getInFlightFences();
    std::vector<VkFence> &getImagesInFlight();
private:
    std::vector<VkSemaphore> imageAvailableSemaphores;
    std::vector<VkSemaphore> renderFinishedSemaphores;
    std::vector<VkFence> inFlightFences;
    std::vector<VkFence> imagesInFlight;
};


#endif //INC_3DGAMEENGINECREATION_SEMAPHORE_HPP
