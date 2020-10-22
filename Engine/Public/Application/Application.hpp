//
// Created by arthur on 21/10/2020.
//

#ifndef INC_3DGAMEENGINECREATION_APPLICATION_HPP
#define INC_3DGAMEENGINECREATION_APPLICATION_HPP

#include "../../Private/Window/Window.hpp"
#include "../Object/Object.hpp"
#include <windows.h>

#include <vector>

class Application
{
public:
    Application();
    ~Application();

public:
    void start(HINSTANCE hInstance);
    void add(Object *object);

private:
    void initObject();

private:
    Window window;
    std::vector<std::unique_ptr<Object>> objectVector;
};


#endif //INC_3DGAMEENGINECREATION_APPLICATION_HPP
