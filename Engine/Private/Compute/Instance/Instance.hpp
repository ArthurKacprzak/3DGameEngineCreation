//
// Created by arthur on 10/10/2020.
//

#ifndef INC_3DGAMEENGINECREATION_INSTANCE_HPP
#define INC_3DGAMEENGINECREATION_INSTANCE_HPP

#include <vulkan/vulkan.h>
#include <vector>

class Surface;

class Instance
{
public:
    Instance();
    ~Instance();

    void release();

public:
    VkInstance getVkInstance();

private:
    std::vector<const char*> getRequiredExtensions();
private:
    VkInstance instance;
};


#endif //INC_3DGAMEENGINECREATION_INSTANCE_HPP
