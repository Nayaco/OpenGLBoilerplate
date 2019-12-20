#include "Model.hpp"

Model::Model(string const &path, bool gamma): gammaCorrection(gamma) {
    loadModel(path);
}

void Model::Draw(Shader const &shader) const {
    for(auto &mesh: meshes) {
        mesh.Draw(shader);
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
        loadMaterialTextures(material, aiTextureType_DIFFUSE, TEX_TYPE::DIFFUSEMAP);
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
    texture_vector specularMaps = 
        loadMaterialTextures(material, aiTextureType_SPECULAR, TEX_TYPE::SPECULARMAP);
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    texture_vector normalMaps = 
        loadMaterialTextures(material, aiTextureType_HEIGHT, TEX_TYPE::NORMALMAP);
    textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
    texture_vector heightMaps = 
        loadMaterialTextures(material, aiTextureType_AMBIENT, TEX_TYPE::HEIGHTMAP);
    textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());
    
    return Mesh(vertices, indices, textures);
}

texture_vector Model::loadMaterialTextures(aiMaterial *mat, aiTextureType ai_tex_type, TEX_TYPE tex_type) {
    texture_vector textures { };
    for(auto i = 0; i < mat->GetTextureCount(ai_tex_type); i++) {
        aiString str;
        Texture texture { };
        mat->GetTexture(ai_tex_type, i, &str);
        for(auto j = 0; j < textures_loaded.size(); j++) {
            if(std::strcmp(textures_loaded[j]._path.c_str(), str.C_Str()) == 0) {
                textures.push_back(textures_loaded[j]);
                goto skip_texture;
            }
        }
        texture.LoadFromFile(str.C_Str(), this->directory, tex_type, false);
        textures.push_back(texture);
        textures_loaded.push_back(texture); 
skip_texture:
    }
    return textures;
}
