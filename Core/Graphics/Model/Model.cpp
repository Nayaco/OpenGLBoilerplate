#include "Model.hpp"

Model::Model(string const &path, bool gamma): gammaCorrection(gamma) {
    loadModel(path);
}

void Model::draw(Shader const &shader) const {
    for(auto &mesh: meshes) {
        mesh.draw(shader);
    }
}

void Model::loadModel(string const &path) {
    const aiScene* scene = import.ReadFile(path, 
                    aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        throw "ERROR::ASSIMP:: " + string(import.GetErrorString());
        return;
    }
    directory = path.substr(0, path.find_last_of('/'));
    processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode *node, const aiScene *scene) {
    for(auto i = 0; i < node->mNumMeshes; i++) {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh, scene));
    }
    for(auto i = 0; i < node->mNumChildren; i++) {
        processNode(node->mChildren[i], scene);
    }
}

Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene) {
    vertex_vector vertices { };
    indice_vector indices { };
    texture_vector textures { };
    auto get_vec2 = [&](const aiVector3D &m2d)->glm::vec2 {
        return glm::vec2(m2d.x, m2d.y);
    };
    auto get_vec3 = [&](const aiVector3D &m3d)->glm::vec3 {
        return glm::vec3(m3d.x, m3d.y, m3d.z);
    };
    
    for(auto i = 0; i < mesh->mNumVertices; i++) {
        Vertex vertex;
        vertex.position = get_vec3(mesh->mVertices[i]); 
        vertex.normal = get_vec3(mesh->mNormals[i]);
        vertex.texCoords = mesh->mTextureCoords[0] ?  
                get_vec2(mesh->mTextureCoords[0][i]):
                glm::vec2(0.0f, 0.0f);     
        vertex.tangent = mesh->mTangents ? 
                get_vec3(mesh->mTangents[i]):
                glm::vec3(0.0f, 0.0f, 0.0f);
        vertex.bitangent = mesh->mBitangents ? 
                get_vec3(mesh->mBitangents[i]):
                glm::vec3(0.0f, 0.0f, 0.0f);
        vertices.push_back(vertex);
    }
    for(auto i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        for(auto j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }
    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];    

    texture_vector diffuseMaps = 
        loadMaterialTextures(material, aiTextureType_DIFFUSE);
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
    texture_vector specularMaps = 
        loadMaterialTextures(material, aiTextureType_SPECULAR);
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    texture_vector normalMaps = 
        loadMaterialTextures(material, aiTextureType_HEIGHT);
    textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
    texture_vector heightMaps = 
        loadMaterialTextures(material, aiTextureType_AMBIENT);
    textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());
    
    return Mesh(vertices, indices, textures);
}

texture_vector Model::loadMaterialTextures(aiMaterial *mat, aiTextureType ai_tex_type) {
    texture_vector textures { };
    for(auto i = 0; i < mat->GetTextureCount(ai_tex_type); i++) {
        aiString str;
        Texture texture;
        mat->GetTexture(ai_tex_type, i, &str);
        for(auto j = 0; j < textures_loaded.size(); j++) {
            if(std::strcmp(textures_loaded[j]._path.c_str(), str.C_Str()) == 0) {
                textures.push_back(textures_loaded[j]);
                goto skip_texture;
            }
        }
        switch (ai_tex_type) {
            case aiTextureType_DIFFUSE: { texture._texture_type = TEX_TYPE::DIFFUSEMAP; break; }
            case aiTextureType_SPECULAR:{ texture._texture_type = TEX_TYPE::SPECULARMAP;break; }
            case aiTextureType_HEIGHT:  { texture._texture_type = TEX_TYPE::HEIGHTMAP;  break; }
            case aiTextureType_AMBIENT: { texture._texture_type = TEX_TYPE::AMBIENTMAP; break; }
        }
        texture = TextureFromFile(string(str.C_Str()), this->directory , false);
        textures.push_back(texture);
        textures_loaded.push_back(texture); 
skip_texture:
    }
    return textures;
}

Texture Model::TextureFromFile(string const &path, string const &directory, bool gamma) {
    Texture texture;
    int width, height, nrChannels;
    string filename = directory + "/" + path;
    unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrChannels, 0);
    if (data) {
        GLenum format;
        switch (nrChannels) {
            case 1: {format = GL_RED; break;}
            case 3: {format = GL_RGB; break;}
            case 4: {format = GL_RGBA; break;}
            default: throw "Model: unknow color space";
        }
        texture._format = format;
        texture._path   = path;
        texture.LoadTexture2D(width, height, data);
        stbi_image_free(data);
    }
    else {
        stbi_image_free(data);
        throw "Model: file "+ filename + " not exists";
    }
}