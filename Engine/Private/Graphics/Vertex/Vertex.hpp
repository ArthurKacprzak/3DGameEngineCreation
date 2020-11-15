//
// Created by arthur on 16/10/2020.
//

#ifndef INC_3DGAMEENGINECREATION_VERTEX_HPP
#define INC_3DGAMEENGINECREATION_VERTEX_HPP

#include <glm/glm.hpp>
#include <vulkan/vulkan.hpp>
#include <vector>
#include <stddef.h>
#include <glm/gtx/hash.hpp>
#include "../Engine/Private/Physics/Maths/Math.hpp"

struct Vertex
{
    static VkVertexInputBindingDescription getBindingDescription();

    static std::array<VkVertexInputAttributeDescription, 3> getAttributeDescriptions();

    glm::vec3 pos;
    glm::vec3 color;
    glm::vec2 texCoord;

    bool operator==(const Vertex& other) const {
        return pos == other.pos && color == other.color && texCoord == other.texCoord;
    }

};

namespace std {
    template<> struct hash<Vertex> {
        size_t operator()(Vertex const& vertex) const {
            return ((hash<glm::vec3>()(vertex.pos) ^ (hash<glm::vec3>()(vertex.color) << 1)) >> 1) ^ (hash<glm::vec2>()(vertex.texCoord) << 1);
        }
    };
}

#endif //INC_3DGAMEENGINECREATION_VERTEX_HPP
