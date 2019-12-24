#include "TerrainMesh.hpp"

TerrainMesh::TerrainMesh(texture_vector textures, imap2d &heightmap, float _width, float _height) {
    mesh_width = _width - 1;
    mesh_height = _height - 1;
    
    genVertexes(heightmap);

    this->textures = textures;
    setupMesh(); 
}

TerrainMesh::~TerrainMesh() {}

void TerrainMesh::draw(Shader const &shader) const {
    unsigned int normalNr   = 1;
    unsigned int heightNr   = 1;
    for(size_t i = 0; i < textures.size(); i++) {
        string name;
        unsigned int number;
        glActiveTexture(GL_TEXTURE0 + i);
        switch (textures[i]._texture_type) {
            case TEX_TYPE::DEFAULT:     {name = "texture_color"; number = 0; break;}
            case TEX_TYPE::NORMALMAP:   {name = "texture_normal"; number = normalNr; normalNr++; break;}
            case TEX_TYPE::HEIGHTMAP:   {name = "texture_height"; number = heightNr; heightNr++; break;}
            default: {throw "TERMESH: texture type unusable";}              
        }
        shader.setInt(name + "_" + std::to_string(number), i);
        textures[i].bind();
    }
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    glActiveTexture(GL_TEXTURE0);
}

void TerrainMesh::setupMesh() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);  
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);	
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(1);	
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tangent));
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, bitangent));
    
    glBindVertexArray(0);
}

void TerrainMesh::genVertexes(imap2d &heightmap) {
    float mesh_batch_width = 1.0f / (float)mesh_width;
    float mesh_batch_height = 1.0f / (float)mesh_height;
    
    for (auto i = 0; i < mesh_width + 1; ++i) {
        for (auto j = 0; j < mesh_height + 1; ++j) {
            float u = mesh_batch_width * i;
            float v = mesh_batch_height * j;
            vertices.push_back(Vertex{position: glm::vec3(u, heightmap[i][j], v),});
        }
    }
    for (auto i = 0; i < mesh_width; ++i) {
        for (auto j = 0; j < mesh_height; ++j) {
            indices.push_back(i * (mesh_height + 1) + j);
            indices.push_back(i * (mesh_height + 1) + j + 1);
            indices.push_back((i + 1) * (mesh_height + 1) + j + 1);

            indices.push_back(i * (mesh_height + 1) + j);
            indices.push_back((i + 1) * (mesh_height + 1) + j);
            indices.push_back((i + 1) * (mesh_height + 1) + j + 1);
        }
    }
}
