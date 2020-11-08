//
// Created by arthur on 24/10/2020.
//

#ifndef INC_3DGAMEENGINECREATION_MODEL_HPP
#define INC_3DGAMEENGINECREATION_MODEL_HPP

#include <string>
#include "../Object/Object.hpp"
#include "../Texture/Texture.hpp"
#include "../../ourLibs/miniobjloader/loader.hpp"

class PublicModel : public Object
{
public:
    PublicModel(std::string objPath);

public:
    void init(Window &window) override;
    void setTexture(Texture *texture_ptr);
    void setOffset(glm::vec3 pos);

private:
    std::string objPath;
    glm::vec3 offset;
    Texture *_texture;

//    std::unique_ptr<Model> model;
};


#endif //INC_3DGAMEENGINECREATION_MODEL_HPP
