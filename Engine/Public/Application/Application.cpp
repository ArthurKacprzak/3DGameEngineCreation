//
// Created by arthur on 21/10/2020.
//

#include "Application.hpp"

Application::Application()
{
}

void Application::start(HINSTANCE hInstance)
{
    this->initObject();
    this->window.init(hInstance);
    this->window.start();
}

void Application::add(Object *object)
{
    this->objectVector.push_back(std::unique_ptr<Object>(object));
}

void Application::initObject()
{
    for (auto & i : this->objectVector) {
        i->init(this->window);
    }
}

Application::~Application()
{
}


