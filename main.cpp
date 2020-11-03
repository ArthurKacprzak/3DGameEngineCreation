//
// Created by arthur on 09/10/2020.
//

#include "Engine/Public/Application/Application.hpp"
#include "Engine/Public/PublicModel/PublicModel.hpp"
#include "Engine/Public/Key/Key.hpp"

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)
{
    Application application;
    PublicModel model;
    PublicModel model2;

    model.setObjPath("../Resources/cube.obj");
    model2.setObjPath("../Resources/cube.obj");
    model2.setOffset({3, 0, 0});


    std::function<void()> s = []() {
        std::cout << "s\n";
    };

    Key key;
    key.setValue('S');
    key.setFunction(s);


    application.addKey(&key);
//    application.addObject(&rect);
    application.addModel(&model);
    application.addModel(&model2);
    application.start(hInstance);
    return 0;
}