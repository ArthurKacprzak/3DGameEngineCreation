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
    this->initKey();
    this->window.init(hInstance);
    this->window.start();
}

void Application::addObject(Object *object)
{
    this->objectVector.push_back(std::unique_ptr<Object>(object));
}

void Application::addModel(PublicModel *model)
{
    this->modelVector.push_back(std::unique_ptr<PublicModel>(model));
}

void Application::addKey(Key *key)
{
    this->keyVector.push_back(std::unique_ptr<Key>(key));
}

void Application::initObject()
{
    for (auto & i : this->objectVector) {
        i->init(this->window);
    }
    for (auto &model : this->modelVector) {
        model->init(this->window);
    }
}

void Application::initKey()
{
    for (auto &i : this->keyVector) {
        this->window.addKey(i->value, i->function);
    }
}

Application::~Application()
{
}



