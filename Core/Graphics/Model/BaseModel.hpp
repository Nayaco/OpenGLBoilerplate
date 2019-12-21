#ifndef BASEMODEL_HPP
#define BASEMODEL_HPP

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Core/Common.hpp"
#include "Core/Graphics/Shader/Shader.hpp"

class BaseModel {
public:
    Assimp::Importer import;
    BaseModel(): import(){ };
    virtual void Draw(const Shader &shader) const = 0;
};

#endif