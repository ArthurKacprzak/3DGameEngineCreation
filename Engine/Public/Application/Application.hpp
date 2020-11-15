//
// Created by arthur on 21/10/2020.
//

#ifndef INC_3DGAMEENGINECREATION_APPLICATION_HPP
#define INC_3DGAMEENGINECREATION_APPLICATION_HPP

#include "../../Private/Window/Window.hpp"
#include "../Object/Object.hpp"
#include <windows.h>
#include "../Key/Key.hpp"
#include "../PublicModel/PublicModel.hpp"

#include <vector>

class Application
{
public:
    Application();
    ~Application();

public:
    enum CameraType { lookat, firstperson };

public:
    void start(HINSTANCE hInstance);
    void addObject(Object *object);
    void addKeyPress(Key *key);
    void addKeyRelease(Key *key);
    void addModel(PublicModel *model);
    void setCamera(CameraType type);

private:
    void initObject();
    void initKey();

private:
    Window window;
    std::vector<std::unique_ptr<Object>> objectVector;
    std::vector<std::unique_ptr<PublicModel>> modelVector;
    std::vector<std::unique_ptr<Key>> keyVectorPress;
    std::vector<std::unique_ptr<Key>> keyVectorRelease;
    Application::CameraType cameraType;
};


#endif //INC_3DGAMEENGINECREATION_APPLICATION_HPP
