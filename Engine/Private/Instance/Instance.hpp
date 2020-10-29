//
// Created by arthur on 10/10/2020.
//

#ifndef INC_3DGAMEENGINECREATION_INSTANCE_HPP
#define INC_3DGAMEENGINECREATION_INSTANCE_HPP

#include <vulkan/vulkan.h>
#include <vector>
//#include <GLFW/glfw3.h>

class Surface;

class Instance
{
public:
    Instance();
    ~Instance();

public:
    VkInstance getVkInstance();

private:
    std::vector<const char*> getRequiredExtensions();
private:
    VkInstance instance;
};


#endif //INC_3DGAMEENGINECREATION_INSTANCE_HPP
