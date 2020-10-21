//
// Created by arthur on 09/10/2020.
//

#include "Engine/Private/Window/Window.hpp"

int main()
{
    Window *window = new Window();
    window->start();
    delete window;
    return 0;
}