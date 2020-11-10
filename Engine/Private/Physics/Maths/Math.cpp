//
// Created by $L9U000-OQ0N5P03710J on 11/10/2020.
//

#include "Math.hpp"

vec3 Math::vec3(float nb) {
    struct vec3 result = {nb, nb, nb};
    return result;
}

vec3 Math::vec3(float x, float y, float z) {
    struct vec3 result = {x, y, z};
    return result;
}

mat3 Math::mat3(float nb) {
    struct mat3 result = {vec3(nb), vec3(nb), vec3(nb)};
    return result;
}

struct mat3 Math::mat3(struct vec3 a, struct vec3 b, struct vec3 c) {
    struct mat3 result = {a, b, c};
    return result;
}

vec4 Math::vec4(float nb) {
    struct vec4 result = {nb, nb, nb, nb};
    return result;
}

vec4 Math::vec4(float x, float y, float z, float f) {
    struct vec4 result = {x, y, z, f};
    return result;
}

mat4 Math::mat4(float nb) {
    struct mat4 result = {vec4(nb), vec4(nb), vec4(nb), vec4(nb)};
    return result;
}

struct mat4 Math::mat4(struct vec4 a, struct vec4 b, struct vec4 c, struct vec4 d) {
    struct mat4 result = {a, b, c, d};
    return result;
}

struct mat4 Math::scaleMat(struct mat4 a, struct vec3 b) {
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            if (x == y) {
                if (x < 3)
                    a.vectors[y].pos[x] *= b.pos[x];
            } else
                a.vectors[y].pos[x] = 0;
        }
    }

    return a;
}

struct mat3 Math::scaleMat(struct mat3 a, struct vec3 b) {
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++) {
            if (x == y)
                a.vectors[y].pos[x] *= b.pos[x];
            else
                a.vectors[y].pos[x] = 0;
        }
    }

    return a;
}

struct mat4 Math::multiplyMat(struct mat4 a, struct mat4 b) {
    struct mat4 result = mat4(0);

    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            for (int count = 0; count < 4; count++) {
                result.vectors[y].pos[x] += a.vectors[y].pos[count] * b.vectors[count].pos[x];
            }
        }
    }

    return result;
}

struct mat3 Math::multiplyMat(struct mat3 a, struct mat3 b) {
    struct mat3 result = mat3(0);

    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++) {
            for (int count = 0; count < 3; count++) {
                result.vectors[y].pos[x] += b.vectors[y].pos[count] * a.vectors[count].pos[x];
            }
        }
    }

    return result;
}
