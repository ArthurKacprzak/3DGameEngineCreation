//
// Created by arthur on 09/10/2020.
//

#include "Engine/Public/Application/Application.hpp"
#include "Engine/Public/PublicModel/PublicModel.hpp"
#include "Engine/Public/Key/Key.hpp"

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)
{
    Application application;
    Object rect;

    float size = 1.f;
    float zPos = -0.1;

    rect.addPoint({{-size, -size, zPos}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}});
    rect.addPoint({{size, -size, zPos}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}});
    rect.addPoint({{size, size, zPos}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}});
    rect.addPoint({{-size, size, zPos}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}});
    rect.setIndices({0, 1, 2, 2, 3, 0});

    PublicModel model;

    model.setPath("../Resources/cube.obj");


    std::function<void()> s = []() {
        std::cout << "s\n";
    };

    Key key;
    key.setValue('S');
    key.setFunction(s);


    application.addKey(&key);
//    application.addObject(&rect);
    application.addModel(&model);
    application.start(hInstance);
    return 0;
}