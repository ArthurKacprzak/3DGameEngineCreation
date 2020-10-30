//
// Created by arthur on 30/10/2020.
//

#ifndef INC_3DGAMEENGINECREATION_KEY_HPP
#define INC_3DGAMEENGINECREATION_KEY_HPP

#include <functional>

class Application;

class Key
{
public:
    Key();

public:
    void setValue(int v);
    void setFunction(std::function<void()> &f);

private:
    int value;
    std::function<void()> function;

private:
    friend Application;
};


#endif //INC_3DGAMEENGINECREATION_KEY_HPP
