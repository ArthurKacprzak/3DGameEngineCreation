//
// Created by arthur on 24/10/2020.
//

#ifndef INC_3DGAMEENGINECREATION_MODEL_HPP
#define INC_3DGAMEENGINECREATION_MODEL_HPP

#include <string>
#include "Object.hpp"
#include "Texture.hpp"
#include "loader.hpp"
#include "Math.hpp"

class PublicModel : public Object
{
public:
    PublicModel(std::string objPath);

public:
    void init(Window &window) override;
    void setTexture(Texture *texture_ptr);
    void setOffset(struct vec3 pos);
    void move(struct vec3 vector);

private:
    std::string objPath;
    struct vec3 offset;
    Texture *_texture;
    Window *window = nullptr;

//    std::unique_ptr<Model> model;
};


#endif //INC_3DGAMEENGINECREATION_MODEL_HPP
