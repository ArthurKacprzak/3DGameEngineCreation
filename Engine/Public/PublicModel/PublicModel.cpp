//
// Created by arthur on 24/10/2020.
//

#include "PublicModel.hpp"

PublicModel::PublicModel()
{

}

void PublicModel::setPath(std::string modelPath)
{
    this->path = modelPath;
}

void PublicModel::init(Window &window)
{
//    Object::init(window);
//    this->model = std::make_unique<Model>(window);
}
