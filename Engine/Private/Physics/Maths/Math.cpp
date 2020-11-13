//
// Created by $L9U000-OQ0N5P03710J on 11/10/2020.
//

#include <cmath>
#include <iostream>
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
    struct mat3 result = {vec3(0), vec3(0), vec3(0)};
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++) {
            if (x == y)
                result.vectors[y].pos[x] = nb;
            else
                result.vectors[y].pos[x] = 0;
        }
    }
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
    struct mat4 result = {vec4(0), vec4(0), vec4(0), vec4(0)};
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            if (x == y)
                result.vectors[y].pos[x] = nb;
            else
                result.vectors[y].pos[x] = 0;
        }
    }
    return result;
}

struct mat4 Math::mat4(struct vec4 a, struct vec4 b, struct vec4 c, struct vec4 d) {
    struct mat4 result = {a, b, c, d};
    return result;
}

struct mat4 Math::scaleMat(struct mat4 a, struct vec3 b) {
    struct mat4 matScale = mat4(0);

    matScale.vectors[0].pos[0] = b.pos[0];
    matScale.vectors[1].pos[1] = b.pos[1];
    matScale.vectors[2].pos[2] = b.pos[2];
    matScale.vectors[3].pos[3] = 1;

    return multiplyMat(a, matScale);
}

struct mat3 Math::scaleMat(struct mat3 a, struct vec3 b) {
    struct mat3 matScale = mat3(0);

    matScale.vectors[0].pos[0] = b.pos[0];
    matScale.vectors[1].pos[1] = b.pos[1];
    matScale.vectors[2].pos[2] = b.pos[2];

    return multiplyMat(a, matScale);
}

struct mat4 Math::multiplyMat(struct mat4 a, struct mat4 b) {
    struct mat4 result = mat4(0);

    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            for (int count = 0; count < 4; count++) {
                result.vectors[y].pos[x] += b.vectors[y].pos[count] * a.vectors[count].pos[x];
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

struct vec4 Math::multiplyMat(struct mat4 a, struct vec4 b) {
    struct vec4 result = vec4(0);

    for (int x = 0; x < 4; x++) {
        for (int count = 0; count < 4; count++) {
            result.pos[x] += b.pos[count] * a.vectors[x].pos[count];
        }
    }

    return result;
}

struct mat4 Math::translateMat(struct mat4 a, struct vec3 b) {
    struct mat4 matScale = mat4(1);

    matScale.vectors[3].pos[0] = b.pos[0];
    matScale.vectors[3].pos[1] = b.pos[1];
    matScale.vectors[3].pos[2] = b.pos[2];

    return multiplyMat(a, matScale);
}

struct mat3 Math::translateMat(struct mat3 a, struct vec3 b) {
    struct mat3 matScale = mat3(1);

    matScale.vectors[2].pos[0] = b.pos[0];
    matScale.vectors[2].pos[1] = b.pos[1];
    matScale.vectors[2].pos[2] = b.pos[2];

    return multiplyMat(a, matScale);
}

double round_up(double value, int decimal_places) {
    const double multiplier = std::pow(10.0, decimal_places);
    return std::floor(value * multiplier) / multiplier;
}

struct mat3 Math::rotateMat(struct mat3 a, struct vec3 b) {
    struct mat3 rotateMatrixX = mat3(1);
    struct mat3 rotateMatrixY = mat3(1);
    struct mat3 rotateMatrixZ = mat3(1);

    rotateMatrixX.vectors[1].pos[1] = float(cos(double(b.pos[0])));
    rotateMatrixX.vectors[1].pos[2] = -1 * float(sin(double(b.pos[0])));
    rotateMatrixX.vectors[2].pos[1] = float(sin(double(b.pos[0])));
    rotateMatrixX.vectors[2].pos[2] = float(cos(double(b.pos[0])));

    rotateMatrixY.vectors[0].pos[0] = float(cos(double(b.pos[1])));
    rotateMatrixY.vectors[0].pos[2] = float(sin(double(b.pos[1])));
    rotateMatrixY.vectors[2].pos[0] = -1 * float(sin(double(b.pos[1])));
    rotateMatrixY.vectors[2].pos[2] = float(cos(double(b.pos[1])));

    rotateMatrixZ.vectors[0].pos[0] = float(cos(double(b.pos[2])));
    rotateMatrixZ.vectors[0].pos[1] = -1 * float(sin(double(b.pos[2])));
    rotateMatrixZ.vectors[1].pos[0] = float(sin(double(b.pos[2])));
    rotateMatrixZ.vectors[1].pos[1] = float(cos(double(b.pos[2])));

    a = multiplyMat(a, rotateMatrixX);
    a = multiplyMat(a, rotateMatrixY);
    a = multiplyMat(a, rotateMatrixZ);
    return a;
}

struct vec4 Math::rotateMat(struct mat4 a, struct vec4 b) {
    struct mat4 rotateMatrixX = mat4(1);
    struct mat4 rotateMatrixY = mat4(1);
    struct mat4 rotateMatrixZ = mat4(1);
    struct vec4 vecTest = vec4(1, 0, 0, 1);

    rotateMatrixX.vectors[1].pos[1] = float(round_up(cos(double(b.pos[0] * pi / 180)), 6));
    rotateMatrixX.vectors[1].pos[2] = -1 * float(round_up(sin(double(b.pos[0] * pi / 180)), 6));
    rotateMatrixX.vectors[2].pos[1] = float(round_up(sin(double(b.pos[0] * pi / 180)), 6));
    rotateMatrixX.vectors[2].pos[2] = float(round_up(cos(double(b.pos[0] * pi / 180)), 6));

    rotateMatrixY.vectors[0].pos[0] = float(round_up(cos(double(b.pos[1] * pi / 180)), 6));
    rotateMatrixY.vectors[0].pos[2] = float(round_up(sin(double(b.pos[1] * pi / 180)), 6));
    rotateMatrixY.vectors[2].pos[0] = -1 * float(round_up(sin(double(b.pos[1] * pi / 180)), 6));
    rotateMatrixY.vectors[2].pos[2] = float(round_up(cos(double(b.pos[1] * pi / 180)), 6));

    rotateMatrixZ.vectors[0].pos[0] = float(round_up(cos(double(b.pos[2] * pi / 180)), 6));
    rotateMatrixZ.vectors[0].pos[1] = -1 * float(round_up(sin(double(b.pos[2] * pi / 180)), 6));
    rotateMatrixZ.vectors[1].pos[0] = float(round_up(sin(double(b.pos[2] * pi / 180)), 6));
    rotateMatrixZ.vectors[1].pos[1] = float(round_up(cos(double(b.pos[2] * pi / 180)), 6));

    for (int y = 0; y < 4; y++) {
        std::cout << " x: " << rotateMatrixZ.vectors[y].pos[0] << " y: " << rotateMatrixZ.vectors[y].pos[1] << " z: " << rotateMatrixZ.vectors[y].pos[2] << " w: " << rotateMatrixZ.vectors[y].pos[3] << std::endl;
    }

    vecTest = multiplyMat(rotateMatrixX, vecTest);
    vecTest = multiplyMat(rotateMatrixY, vecTest);
    vecTest = multiplyMat(rotateMatrixZ, vecTest);
    return vecTest;
}