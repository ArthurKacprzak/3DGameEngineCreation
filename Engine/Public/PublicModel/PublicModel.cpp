//
// Created by arthur on 24/10/2020.
//

#include "PublicModel.hpp"

#include <utility>

PublicModel::PublicModel(std::string objPath)
{
    this->objPath = std::move(objPath);
    offset = {0, 0, 0};
}

void PublicModel::init(Window &window)
{
    this->window = &window;
    miniobj::loader loader;
    miniobj::attrib_t attribM;
    std::vector<miniobj::shape_t> shapesM;
    loader.load(&attribM, &shapesM, objPath);

    std::unordered_map<Vertex, uint32_t> uniqueVertices{};

    for (const auto& shape : shapesM) {
        for (const auto& index : shape.mesh.indices) {
            Vertex vertex{};

            vertex.pos = {
                    attribM.vertices[3 * index.vertex_index + 0] + offset.pos[0],
                    attribM.vertices[3 * index.vertex_index + 1] + offset.pos[1],
                    attribM.vertices[3 * index.vertex_index + 2] + offset.pos[2]
            };

            vertex.texCoord = {
                    attribM.texcoords[2 * index.texcoord_index + 0],
                    1.0f - attribM.texcoords[2 * index.texcoord_index + 1]
            };

            vertex.color = {1.0f, 1.0f, 1.0f};

            if (uniqueVertices.count(vertex) == 0) {
                uniqueVertices[vertex] = static_cast<uint32_t>(window.getVertices().size());
                window.addVertice(vertex);
            }

            window.addIndex(uniqueVertices[vertex]);
        }
    }
}

void PublicModel::setOffset(struct vec3 pos)
{
    this->offset = pos;
}

void PublicModel::setTexture(Texture *texture_ptr)
{
    _texture = texture_ptr;
}

void PublicModel::move(glm::vec3 vector)
{
    this->window->move(vector);
    std::cout << "move\n";
}
