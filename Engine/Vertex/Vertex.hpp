//
// Created by arthur on 16/10/2020.
//

#ifndef INC_3DGAMEENGINECREATION_VERTEX_HPP
#define INC_3DGAMEENGINECREATION_VERTEX_HPP

#include <glm/glm.hpp>
#include <vulkan/vulkan.hpp>
#include <vector>
#include <stddef.h>

class Vertex
{
public:
    Vertex(glm::vec2 pos, glm::vec3 color, glm::vec2 texCoord);

public:
    static VkVertexInputBindingDescription getBindingDescription();

    static std::array<VkVertexInputAttributeDescription, 3> getAttributeDescriptions();

private:
    glm::vec2 pos;
    glm::vec3 color;
    glm::vec2 texCoord;
};


#endif //INC_3DGAMEENGINECREATION_VERTEX_HPP
