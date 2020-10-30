//
// Created by arthur on 10/10/2020.
//

#include "Semaphore.hpp"
#include "../../Window/Window.hpp"

Semaphore::Semaphore(ImageViews &imageViews, Device &device)
{
    imageAvailableSemaphores.resize(Window::MAX_FRAMES_IN_FLIGHT);
    renderFinishedSemaphores.resize(Window::MAX_FRAMES_IN_FLIGHT);
    inFlightFences.resize(Window::MAX_FRAMES_IN_FLIGHT);
    imagesInFlight.resize(imageViews.getSwapChainImages().size(), VK_NULL_HANDLE);

    VkSemaphoreCreateInfo semaphoreInfo{};
    semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

    VkFenceCreateInfo fenceInfo{};
    fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

    for (size_t i = 0; i < Window::MAX_FRAMES_IN_FLIGHT; i++) {
        if (vkCreateSemaphore(device.getDevice(), &semaphoreInfo, nullptr, &imageAvailableSemaphores[i]) != VK_SUCCESS ||
            vkCreateSemaphore(device.getDevice(), &semaphoreInfo, nullptr, &renderFinishedSemaphores[i]) != VK_SUCCESS ||
            vkCreateFence(device.getDevice(), &fenceInfo, nullptr, &inFlightFences[i]) != VK_SUCCESS) {
            throw std::runtime_error("failed to create synchronization objects for a frame!");
        }
    }
}

std::vector<VkSemaphore> &Semaphore::getImageAvailableSemaphores()
{
    return imageAvailableSemaphores;
}

std::vector<VkSemaphore> &Semaphore::getRenderFinishedSemaphores()
{
    return renderFinishedSemaphores;
}

std::vector<VkFence> &Semaphore::getInFlightFences()
{
    return inFlightFences;
}

std::vector<VkFence> &Semaphore::getImagesInFlight()
{
    return imagesInFlight;
}
