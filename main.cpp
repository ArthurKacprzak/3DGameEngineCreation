//
// Created by arthur on 09/10/2020.
//

#include "Engine/Public/Application/Application.hpp"
#include "Engine/Public/PublicModel/PublicModel.hpp"
#include "Engine/Public/Texture/Texture.hpp"
#include "Engine/Public/Key/Key.hpp"

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)
{
    Application application;
    PublicModel model("../Resources/cube.obj");
    PublicModel model2("../Resources/cube.obj");
    Texture sand("../textures/sand.jpg");
    Texture face("../textures/texture.jpg");

    model.setTexture(&sand);
    model2.setTexture(&face);
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