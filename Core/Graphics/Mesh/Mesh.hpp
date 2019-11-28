#ifndef MESH_HPP
#define MESH_HPP

#include <glad/glad.h> 
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Core/Graphics/Shader.hpp"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
using std::vector;
using std::stringstream;
using std::ifstream;

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
    glm::vec3 Tangent;
    glm::vec3 Bitangent;
};

struct Texture {
    unsigned int id;
    string type;
    string path;
};

class Mesh {
public:
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    vector<Texture> textures;
    unsigned int VAO;
    explicit Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);
    void Draw(Shader &shader);
private:
    unsigned int VBO, EBO;
    void setupMesh();
};

#endif