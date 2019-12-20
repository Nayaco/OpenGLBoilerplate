#ifndef MODEL_HPP
#define MODEL_HPP

#include "Core/Common.hpp"
#include "Core/Graphics/Mesh/Mesh.hpp"
#include "Core/Graphics/Shader/Shader.hpp"
#include "Core/ExceptionHandle/ErrLog.hpp"

#include "BaseModel.hpp"

unsigned int TextureFromFile(const char *path, const string &directory, bool gamma = false);

class Model : public BaseModel {
public:
    string directory;
    mesh_vector meshes;
    texture_vector textures_loaded;
    bool gammaCorrection;
    
    Model(string const &path, bool gamma = false);
    virtual void Draw(Shader const &shader) const override;
private:
    void loadModel(string const &path);
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    texture_vector Model::loadMaterialTextures(aiMaterial *mat, aiTextureType ai_tex_type, TEX_TYPE tex_type);
};

#endif