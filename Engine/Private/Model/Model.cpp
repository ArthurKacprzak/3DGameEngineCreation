//
// Created by arthur on 20/10/2020.
//

#include "Model.hpp"

#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>
#include "../Window/Window.hpp"
#include <iostream>
#include "../ourLibs/miniobjloader/loader.hpp"

Model::Model(Window *window)
{
    miniobj::loader loader;
    miniobj::attrib_t attribM;
    std::vector<miniobj::shape_t> shapesM;
//    tinyobj::attrib_t attrib;
//    std::vector<tinyobj::shape_t> shapes;
//    std::vector<tinyobj::material_t> materials;
//    std::string warn, err;

//    if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, Model::getModelPath().c_str())) {
//        throw std::runtime_error(warn + err);
//    }
    std::cout << Model::getModelPath() << "\n";
    loader.load(&attribM, &shapesM, Model::getModelPath());

    std::unordered_map<Vertex, uint32_t> uniqueVertices{};

    for (const auto& shape : shapesM) {
        for (const auto& index : shape.mesh.indices) {
            Vertex vertex{};

            vertex.pos = {
                    attribM.vertices[3 * index.vertex_index + 0],
                    attribM.vertices[3 * index.vertex_index + 1],
                    attribM.vertices[3 * index.vertex_index + 2]
            };

            vertex.texCoord = {
                    attribM.texcoords[2 * index.texcoord_index + 0],
                    1.0f - attribM.texcoords[2 * index.texcoord_index + 1]
            };

            vertex.color = {1.0f, 1.0f, 1.0f};

            if (uniqueVertices.count(vertex) == 0) {
                uniqueVertices[vertex] = static_cast<uint32_t>(window->getVertices().size());
                window->addVertice(vertex);
            }

            std::cout << uniqueVertices[vertex] <<"\n";

            window->addIndex(uniqueVertices[vertex]);
        }
    }
}

std::string Model::getTexturePath()
{
    return "../textures/viking_room.png";
}

std::string Model::getModelPath()
{
    return "../Resources/viking_room.obj";
}


