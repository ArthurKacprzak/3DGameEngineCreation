//
// Created by $L9U000-OQ0N5P03710J on 11/8/2020.
//

#ifndef INC_3DGAMEENGINECREATION_TRIPHYSICS_HPP
#define INC_3DGAMEENGINECREATION_TRIPHYSICS_HPP

#include <vector>

typedef struct vec3 {
    float x, y, z;
} vec3;

typedef struct triangle {
    vec3 triangle[3];
} triangle;

typedef struct mesh {
    std::vector<triangle> triangles;
} mesh;

class TriPhysics {
private:
    mesh objectMesh;

public:
    TriPhysics();
};


#endif //INC_3DGAMEENGINECREATION_TRIPHYSICS_HPP
