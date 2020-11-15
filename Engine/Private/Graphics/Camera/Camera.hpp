//
// Created by arthur on 31/10/2020.
//

#ifndef INC_3DGAMEENGINECREATION_CAMERA_HPP
#define INC_3DGAMEENGINECREATION_CAMERA_HPP

#include <cmath>
#include "Math.hpp"

#include <iostream>
class Camera
{

private:
    float fov;
    float znear, zfar;

    void updateViewMatrix()
    {
        struct mat4 rotM = Math::rotateMat(1, Math::vec4(rotation.pos[0] * (flipY ? -1.0f : 1.0f), rotation.pos[1], rotation.pos[2], 0));

        struct vec3 translation = position;
        if (flipY) {
            translation.pos[1] *= -1.0f;
        }

        struct mat4 transM = Math::translateMat(Math::mat4(1.0f), translation);

        if (type == CameraType::firstperson)
        {
            matrices.view = Math::multiplyMat(rotM, transM);
        }
        else
        {
            matrices.view = Math::multiplyMat(transM, rotM);
        }

        viewPos = Math::multiplyMat(Math::vec4(position.pos[0], position.pos[1], position.pos[2], 0.0f), Math::vec4(-1.0f, 1.0f, -1.0f, 1.0f));

        updated = true;
    };
public:
    enum CameraType { lookat, firstperson };
    CameraType type = CameraType::lookat;

    struct vec3 rotation;
    struct vec3 position;
    struct vec4 viewPos;

    float rotationSpeed = 1.0f;
    float movementSpeed = 1.0f;

    bool updated = false;
    bool flipY = true;

    struct
    {
        struct mat4 perspective;
        struct mat4 view;
    } matrices;

    struct
    {
        bool left = false;
        bool right = false;
        bool up = false;
        bool down = false;
    } keys;

    bool moving()
    {
        return keys.left || keys.right || keys.up || keys.down;
    }

    float getNearClip() {
        return znear;
    }

    float getFarClip() {
        return zfar;
    }

    void setPerspective(float fov, float aspect, float znear, float zfar)
    {
        this->fov = fov;
        this->znear = znear;
        this->zfar = zfar;
        matrices.perspective = Math::perspectiveMat(fov, aspect, znear, zfar);
        if (flipY) {
            matrices.perspective.vectors[1].pos[1] *= -1.0f;
        }
    };

    void updateAspectRatio(float aspect)
    {
        matrices.perspective = Math::perspectiveMat(fov, aspect, znear, zfar);
        if (flipY) {
            matrices.perspective.vectors[1].pos[1] *= -1.0f;
        }
    }

    void setPosition(struct vec3 position)
    {
        this->position = position;
        updateViewMatrix();
    }

    void setRotation(struct vec3 rotation)
    {
        this->rotation = rotation;
        updateViewMatrix();
    }

    void rotate(struct vec3 delta)
    {
        this->rotation = Math::addMat(this->rotation, delta);
        updateViewMatrix();
    }

    void setTranslation(struct vec3 translation)
    {
        this->position = translation;
        updateViewMatrix();
    };

    void translate(struct vec3 delta)
    {
        this->position = Math::addMat(this->position, delta);
        updateViewMatrix();
    }

    void setRotationSpeed(float rotationSpeed)
    {
        this->rotationSpeed = rotationSpeed;
    }

    void setMovementSpeed(float movementSpeed)
    {
        this->movementSpeed = movementSpeed;
    }

    void update(float deltaTime)
    {
        updated = false;
        if (type == CameraType::firstperson)
        {
            if (moving())
            {
                struct vec3 camFront = Math::vec3(float(-cos(double(rotation.pos[0])) * sin(double(rotation.pos[1]))), float(sin(double(rotation.pos[0]))), float(cos(double(rotation.pos[0])) * cos(double(rotation.pos[1]))));
                camFront = Math::normalizeVec(camFront);

                float moveSpeed = deltaTime * movementSpeed;

                if (keys.up)
                    position = Math::addMat(position, Math::multiplyMat(camFront, moveSpeed));
                if (keys.down)
                    position = Math::substractMat(position, Math::multiplyMat(camFront, moveSpeed));
                if (keys.left)
                    position = Math::substractMat(position, Math::normalizeVec(Math::crossVec(camFront, Math::multiplyMat(Math::vec3(0.0f, 1.0f, 0.0f), moveSpeed))));
                if (keys.right)
                    position = Math::addMat(position, Math::normalizeVec(Math::crossVec(camFront, Math::multiplyMat(Math::vec3(0.0f, 1.0f, 0.0f), moveSpeed))));

                updateViewMatrix();
            }
        }
    };

    // Update camera passing separate axis data (gamepad)
    // Returns true if view or position has been changed
    bool updatePad(struct vec2 axisLeft, struct vec2 axisRight, float deltaTime)
    {
        bool retVal = false;

        if (type == CameraType::firstperson)
        {
            // Use the common console thumbstick layout
            // Left = view, right = move

            const float deadZone = 0.0015f;
            const float range = 1.0f - deadZone;

            struct vec3 camFront = Math::vec3(float(-cos(double(rotation.pos[0])) * sin(double(rotation.pos[1]))), float(sin(double(rotation.pos[0]))), float(cos(double(rotation.pos[0])) * cos(double(rotation.pos[1]))));
            camFront = Math::normalizeVec(camFront);

            float moveSpeed = deltaTime * movementSpeed * 2.0f;
            float rotSpeed = deltaTime * rotationSpeed * 50.0f;

            // Move
            if (fabsf(axisLeft.pos[1]) > deadZone)
            {
                float pos = (fabsf(axisLeft.pos[1]) - deadZone) / range;
                Math::substractMat(position, Math::multiplyMat(camFront, pos * ((axisLeft.pos[1] < 0.0f) ? -1.0f : 1.0f) * moveSpeed));
                retVal = true;
            }
            if (fabsf(axisLeft.pos[0]) > deadZone)
            {
                float pos = (fabsf(axisLeft.pos[0]) - deadZone) / range;
                position = Math::addMat(position, Math::multiplyMat(Math::normalizeVec(Math::crossVec(camFront, Math::vec3(0.0f, 1.0f, 0.0f))), pos * ((axisLeft.pos[0] < 0.0f) ? -1.0f : 1.0f) * moveSpeed));
                retVal = true;
            }

            // Rotate
            if (fabsf(axisRight.pos[0]) > deadZone)
            {
                float pos = (fabsf(axisRight.pos[0]) - deadZone) / range;
                rotation.pos[1] += pos * ((axisRight.pos[0] < 0.0f) ? -1.0f : 1.0f) * rotSpeed;
                retVal = true;
            }
            if (fabsf(axisRight.pos[1]) > deadZone)
            {
                float pos = (fabsf(axisRight.pos[1]) - deadZone) / range;
                rotation.pos[0] -= pos * ((axisRight.pos[1] < 0.0f) ? -1.0f : 1.0f) * rotSpeed;
                retVal = true;
            }
        }
        else
        {
            // todo: move code from example base class for look-at
        }

        if (retVal)
        {
            updateViewMatrix();
        }

        return retVal;
    }
};


#endif //INC_3DGAMEENGINECREATION_CAMERA_HPP
