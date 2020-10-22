//
// Created by Black Moustache on 21/10/2020.
//

#ifndef INC_3DGAMEENGINECREATION_LOADER_HPP
#define INC_3DGAMEENGINECREATION_LOADER_HPP

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include "tools.hpp"

namespace miniobj {

    typedef struct {
        std::vector<float> vertices;
        std::vector<float> texcoords;
        std::vector<float> normal;
    } attrib_t;

    typedef struct {
        int vertex_index;
        int normal_index;
        int texcoord_index;
    } index_t;

    typedef struct {
        std::vector<index_t> indices;
    } mesh_t;

    typedef struct {
        std::string name;
        mesh_t mesh;
    } shape_t;

    class loader {
    public:
        bool load(attrib_t *attrib, std::vector<miniobj::shape_t> *shape, std::string path);

    private:
        void hadleLine(std::string line);
        void fillIndex(std::string token);

        std::vector<shape_t> *_shapes;
        shape_t currentShape;
        attrib_t *_attrib;
    };
}


#endif //INC_3DGAMEENGINECREATION_LOADER_HPP
