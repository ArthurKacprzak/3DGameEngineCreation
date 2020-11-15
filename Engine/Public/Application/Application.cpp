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
    if (this->cameraType == Application::CameraType::lookat) {
        this->window.setCameraType(Camera::CameraType::lookat);
    } else {
        this->window.setCameraType(Camera::CameraType::firstperson);
    }
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

void Application::addKeyPress(Key *key)
{
    this->keyVectorPress.push_back(std::unique_ptr<Key>(key));
}

void Application::addKeyRelease(Key *key)
{
    this->keyVectorRelease.push_back(std::unique_ptr<Key>(key));
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
    for (auto &i : this->keyVectorPress) {
        this->window.addKeyPress(i->value, i->function);
    }
    for (auto &i : this->keyVectorRelease) {
        this->window.addKeyRelease(i->value, i->function);
    }
}

Application::~Application()
{
}

void Application::setCamera(Application::CameraType type)
{
    this->cameraType = type;
}



