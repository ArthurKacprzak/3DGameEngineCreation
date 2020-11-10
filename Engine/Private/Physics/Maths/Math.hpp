//
// Created by $L9U000-OQ0N5P03710J on 11/10/2020.
//

#ifndef INC_3DGAMEENGINECREATION_MATH_HPP
#define INC_3DGAMEENGINECREATION_MATH_HPP

#include <vector>

struct vec3 {
    float pos[3];
};

struct mat3 {
    vec3 vectors[3];
};

struct vec4 {
    float pos[4];
};

struct mat4 {
    vec4 vectors[4];
};

class Math {
public:
    static struct vec3 vec3(float nb);
    static struct vec3 vec3(float x, float y, float z);
    static struct mat3 mat3(float nb);
    static struct mat3 mat3(struct vec3 a, struct vec3 b, struct vec3 c);
    static struct vec4 vec4(float nb);
    static struct vec4 vec4(float x, float y, float z, float f);
    static struct mat4 mat4(float nb);
    static struct mat4 mat4(struct vec4 a, struct vec4 b, struct vec4 c, struct vec4 d);

    static struct mat4 scaleMat(struct mat4 a, struct vec3 b);
    static struct mat3 scaleMat(struct mat3 a, struct vec3 b);

    static struct mat4 multiplyMat(struct mat4 a, struct mat4 b);
    static struct mat3 multiplyMat(struct mat3 a, struct mat3 b);

    static struct mat4 translateMat(struct mat4 a, struct vec3 b);
    static struct mat3 translateMat(struct mat3 a, struct vec3 b);
};


#endif //INC_3DGAMEENGINECREATION_MATH_HPP
