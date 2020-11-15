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


    std::function<void()> s = []() {
        std::cout << "s\n";
    };

    Key *key = new Key();
    key->setValue('S');
    key->setFunction(s);


    application.addKey(key);
    application.start(hInstance);
    return 0;
}