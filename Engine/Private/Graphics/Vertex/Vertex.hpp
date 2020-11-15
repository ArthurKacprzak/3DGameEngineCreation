//
// Created by arthur on 16/10/2020.
//

#ifndef INC_3DGAMEENGINECREATION_VERTEX_HPP
#define INC_3DGAMEENGINECREATION_VERTEX_HPP

#include <vulkan/vulkan.hpp>
#include <vector>
#include <stddef.h>
#include "Math.hpp"

struct Vertex
{
    static VkVertexInputBindingDescription getBindingDescription();

    static std::array<VkVertexInputAttributeDescription, 3> getAttributeDescriptions();

    struct vec3 pos;
    struct vec3 color;
    struct vec2 texCoord;

    bool operator==(const Vertex& other) const {
        return pos.pos[0] == other.pos.pos[0] && other.pos.pos[1] == pos.pos[1] && other.pos.pos[2] == pos.pos[2]
        && color.pos[0] == other.color.pos[0] && color.pos[1] == other.color.pos[1] && color.pos[2] == other.color.pos[2]
        && texCoord.pos[0] == other.texCoord.pos[0]&& texCoord.pos[1] == other.texCoord.pos[1];
    }
};

namespace std {
    template<> struct hash<Vertex> {
        size_t operator()(Vertex const& vertex) const {
            return 1;
        }
    };
}

#endif //INC_3DGAMEENGINECREATION_VERTEX_HPP
