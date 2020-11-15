//
// Created by arthur on 09/10/2020.
//

#include "Application.hpp"

void createRect(Application &application, float zPos, float size, std::vector<uint32_t> index)
{
    Object *rect = new Object();
    rect->addPoint({{-size, -size, zPos}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}});
    rect->addPoint({{size, -size, zPos}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}});
    rect->addPoint({{size, size, zPos}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}});
    rect->addPoint({{-size, size, zPos}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}});
    rect->setIndices(index);
    application.addObject(rect);
}

void setKeys(PublicModel *model, Application &application)
{
    std::function<void()> sPress = [model]() {
        model->move({0.001, 0, 0});
    };

    std::function<void()> sRelease = [model]() {
        model->move({0, 0, 0});
    };

    Key *keyP = new Key();
    keyP->setValue('S');
    keyP->setFunction(sPress);
    Key *keyR = new Key();
    keyR->setValue('S');
    keyR->setFunction(sRelease);


    application.addKeyPress(keyP);
    application.addKeyRelease(keyR);
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)
{
    Application application;

    createRect(application, -1, 1.f, {0, 1, 2, 2, 3, 0});
    createRect(application, -1.1, 1.f, {4, 5, 6, 6, 7, 4});

    PublicModel *model = new PublicModel("Resources/viking_room.obj");
    PublicModel *model2 = new PublicModel("Resources/cube.obj");
    Texture sand("textures/sand.jpg");
    Texture face("textures/texture.jpg");

    model->setTexture(&sand);
    model2->setTexture(&face);
    model2->setOffset({3, 0, 0});
    application.addModel(model);
    application.addModel(model2);

    setKeys(model, application);


    application.setCamera(Application::CameraType::firstperson);
    application.start(hInstance);
    return 0;
}