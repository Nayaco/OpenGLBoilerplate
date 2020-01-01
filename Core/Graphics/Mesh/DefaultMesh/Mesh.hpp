#ifndef MESH_HPP
#define MESH_HPP

#include "Core/Common.hpp"
#include "Core/Graphics/Shader/Shader.hpp"
#include "Core/Graphics/Texture/Texture.hpp"
#include "Core/Graphics/Mesh/BaseMesh.hpp"

class Mesh : public BaseMesh {
public:
    vertex_vector vertices;
    indice_vector indices;
    texture_vector textures;
    unsigned int VAO;
    explicit Mesh(vertex_vector vertices, indice_vector indices, texture_vector textures);
    virtual void draw(Shader const &shader) const override;
private:
    unsigned int VBO, EBO;
    virtual void setupMesh() override;
};
using mesh_vector = std::vector<Mesh>;
#endif