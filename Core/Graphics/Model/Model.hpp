#ifndef MODEL_HPP
#define MODEL_HPP

#include "Core/Common.hpp"
#include "Core/Graphics/Mesh/DefaultMesh/Mesh.hpp"
#include "Core/Graphics/Shader/Shader.hpp"
#include "Core/ResourceManager/ResourceManager.hpp"

#include "BaseModel.hpp"

class Model : public BaseModel {
public:
    string directory;
    mesh_vector meshes;
    texture_vector textures_loaded;
    bool gammaCorrection;
    
    Model(string const &path, bool gamma = false);
    virtual void draw(Shader const &shader) const override;
private:
    void loadModel(string const &path);
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    texture_vector loadMaterialTextures(aiMaterial *mat, aiTextureType ai_tex_type);

    static Texture TextureFromFile(string const &path, string const &directory, bool gamma = false);
};

using default_model_vector = vector<Model>;

#endif