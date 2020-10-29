//
// Created by arthur on 09/10/2020.
//

#include "Engine/Public/Application/Application.hpp"
#include "Engine/Public/PublicModel/PublicModel.hpp"

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

    model.setPath("../Resources/viking_room.obj");

    application.add(&rect);
    application.start(hInstance);
    return 0;
}