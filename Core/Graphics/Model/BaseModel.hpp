#ifndef BASEMODEL_HPP
#define BASEMODEL_HPP

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Core/Graphics/Shader.hpp"

#include <string>
using std::string;
class BaseModel {
public:
    string directory;
    Assimp::Importer import;
    BaseModel(): import(){ };
    virtual void Draw(Shader &shader) = 0;
};

#endif