//
// Created by arthur on 09/10/2020.
//

#include "Engine/Public/Application/Application.hpp"
#include "Engine/Public/PublicModel/PublicModel.hpp"
#include "Engine/Public/Texture/Texture.hpp"
#include "Engine/Public/Key/Key.hpp"

#include "Engine/Private/Physics/Maths/Math.hpp"
#include <glm/gtx/string_cast.hpp>


void createRect(Application &application, Object &rect, float zPos, float size, std::vector<uint32_t> index)
{
    rect.addPoint({{-size, -size, zPos}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}});
    rect.addPoint({{size, -size, zPos}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}});
    rect.addPoint({{size, size, zPos}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}});
    rect.addPoint({{-size, size, zPos}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}});
    rect.setIndices(index);
    application.addObject(&rect);
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)
{
    Application application;
    Object rect;
    createRect(application, rect, -1, 1.f, {0, 1, 2, 2, 3, 0});
    Object rect2;
    createRect(application, rect2, -1.1, 1.f, {4, 5, 6, 6, 7, 4});

    PublicModel model("Resources/cube.obj");
    PublicModel model2("Resources/cube.obj");
    PublicModel scene("Resources/viking_room.obj");
    Texture viking_room("textures/viking_room.png");
    Texture sand("textures/sand.jpg");
    Texture face("textures/texture.jpg");

    model.setTexture(&sand);
    model2.setTexture(&face);
    scene.setTexture(&viking_room);
    scene.setOffset({0, 0, -5});
    model2.setOffset({0, 0, 3});
    application.addModel(&scene);
    application.addModel(&model);
    application.addModel(&model2);


    std::function<void()> s = []() {
        std::cout << "s\n";
    };

    Key key;
    key.setValue('S');
    key.setFunction(s);

    // Exemple de matrices
    /*
     * Matrice complété avec un nombre (float)
     * mat4 testmat4 = Math::mat4(5);
     * matrice complété avec des Vecteurs(float)
     * mat3 testmat3 = Math::mat3(Math::vec3(1), Math::vec3(1), Math::vec3(1, 2, 1));
     * Scale de la matrice testMath4 par le vecteur 2,2,2
     * mat4 testResult = Math::scaleMat(testmat4, Math::vec3(2));
    */

    application.addKey(&key);
    application.start(hInstance);
    return 0;
}