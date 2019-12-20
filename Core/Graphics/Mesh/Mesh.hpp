#ifndef MESH_HPP
#define MESH_HPP

#include "Core/Common.hpp"
#include "Core/Graphics/Shader/Shader.hpp"
#include "Core/Graphics/Texture/Texture.hpp"
struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
    glm::vec3 tangent;
    glm::vec3 bitangent;
};
using vertex_vector = vector<Vertex>;
class Mesh {
public:
    vertex_vector vertices;
    indice_vector indices;
    texture_vector textures;
    unsigned int VAO;
    explicit Mesh(vertex_vector  vertices, indice_vector indices, texture_vector textures);
    void Draw(Shader const &shader) const;
private:
    unsigned int VBO, EBO;
    void setupMesh();
};
using mesh_vector = vector<Mesh>;
#endif