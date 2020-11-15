//
// Created by $L9U000-OQ0N5P03710J on 11/10/2020.
//

#include <cmath>
#include "Math.hpp"

struct vec2 Math::vec2(float nb) {
    struct vec2 result = {nb, nb};
    return result;
}

struct vec2 Math::vec2(float x, float y) {
    struct vec2 result = {x, y};
    return result;
}

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

    return matScale;
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

struct vec4 Math::multiplyMat(struct vec4 a, struct vec4 b) {
    struct vec4 result = vec4(0);

    for (int i = 0; i < 4; i++)
        result.pos[i] += a.pos[i] * b.pos[i];
    return result;
}

struct vec3 Math::multiplyMat(struct vec3 a, float b) {
    struct vec3 result = vec3(0);

    for (int i = 0; i < 3; i++)
        result.pos[i] = a.pos[i] * b;
    return result;
}


struct vec4 Math::multiplyMat(struct vec4 a, float b) {
    struct vec4 result = vec4(0);

    for (int i = 0; i < 4; i++)
        result.pos[i] = a.pos[i] * b;
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

struct mat4 Math::rotateMat(float a, struct vec4 b) {
    float X = b.pos[0];
    float Y = b.pos[1];
    float Z = b.pos[2];
    struct mat4 rotateMatrix = mat4(a);

    rotateMatrix.vectors[0].pos[0] = float(round_up(cos(double(toRadian(Z))) * cos(double(toRadian(Y))), 6));
    rotateMatrix.vectors[0].pos[1] = float(round_up((cos(double(toRadian(Z))) * sin(double(toRadian(Y))) * sin(double(toRadian(X)))) - (sin(double(toRadian(Z))) * cos(double(toRadian(X)))), 6));
    rotateMatrix.vectors[0].pos[2] = float(round_up((cos(double(toRadian(Z))) * sin(double(toRadian(Y))) * cos(double(toRadian(X)))) + (sin(double(toRadian(Z))) * sin(double(toRadian(X)))), 6));
    rotateMatrix.vectors[1].pos[0] = float(round_up(sin(double(toRadian(Z))) * cos(double(toRadian(Y))), 6));
    rotateMatrix.vectors[1].pos[1] = float(round_up((sin(double(toRadian(Z))) * sin(double(toRadian(Y))) * sin(double(toRadian(X)))) + (cos(double(toRadian(Z))) * cos(double(toRadian(X)))), 6));
    rotateMatrix.vectors[1].pos[2] = float(round_up((sin(double(toRadian(Z))) * sin(double(toRadian(Y))) * cos(double(toRadian(X)))) - (cos(double(toRadian(Z))) * sin(double(toRadian(X)))), 6));
    rotateMatrix.vectors[2].pos[0] = float(round_up(- sin(double(toRadian(Y))), 6));
    rotateMatrix.vectors[2].pos[1] = float(round_up(cos(double(toRadian(Y))) * sin(double(toRadian(X))), 6));
    rotateMatrix.vectors[2].pos[2] = float(round_up(cos(double(toRadian(Y))) * cos(double(toRadian(X))), 6));

    return rotateMatrix;
}

struct vec3 Math::substractMat(struct vec3 a, struct vec3 b) {
    struct vec3 result = vec3(0);

    for (int i = 0; i < 3; i++)
        result.pos[i] += a.pos[i] - b.pos[i];
    return result;
}

struct vec3 Math::normalizeVec(struct vec3 a) {
    auto normal = float(sqrt(double((a.pos[0] * a.pos[0]) + (a.pos[1] * a.pos[1]) + (a.pos[2] * a.pos[2]))));

    return vec3(a.pos[0] / normal, a.pos[1] / normal, a.pos[2] / normal);
}

struct vec3 Math::crossVec(struct vec3 a, struct vec3 b) {
    struct vec3 result = vec3(0);

    result.pos[0] = (a.pos[1] * b.pos[2]) - (a.pos[2] * b.pos[1]);
    result.pos[1] = (a.pos[2] * b.pos[0]) - (a.pos[0] * b.pos[2]);
    result.pos[2] = (a.pos[0] * b.pos[1]) - (a.pos[1] * b.pos[0]);

    return result;
}

struct vec3 Math::addMat(struct vec3 a, struct vec3 b) {
    return vec3(a.pos[0] + b.pos[0], a.pos[1] + b.pos[1],a.pos[2] + b.pos[2]);
}

float Math::toRadian(float a) {
    return float(a * piMath / 180);
}

struct mat4 Math::perspectiveMat(float fov, float aspect, float znear, float zfar) {
    struct mat4 result = mat4(0.0f);
    float zrange = zfar - znear;
    float tanHalfFOV = tanf(toRadian(float(fov / 2.f)));

    result.vectors[0].pos[0] = 1.0f / (tanHalfFOV * aspect);
    result.vectors[1].pos[1] = 1.0f / tanHalfFOV;
    result.vectors[2].pos[2] = (-znear - zfar) / zrange;
    result.vectors[2].pos[3] = -1;
    result.vectors[3].pos[2] = -(2.0f * zfar * znear) / zrange;

    return result;
}