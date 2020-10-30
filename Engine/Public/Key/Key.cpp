//
// Created by arthur on 30/10/2020.
//

#include "Key.hpp"

Key::Key()
{

}

void Key::setValue(int v)
{
    this->value = v;
}

void Key::setFunction(std::function<void()> &f)
{
    this->function = f;
}
