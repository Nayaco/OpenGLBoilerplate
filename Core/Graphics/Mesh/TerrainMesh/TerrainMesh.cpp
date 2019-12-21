#include "TerrainMesh.hpp"

TerrainMesh::TerrainMesh(texture_vector textures, unsigned int _width, unsigned int _height) 
    :vertices { 
        Vertex{position: glm::vec3(-_width, _height, 0.0f),},
        Vertex{position: glm::vec3(-_width,-_height, 0.0f),},
        Vertex{position: glm::vec3( _width,-_height, 0.0f),},
        Vertex{position: glm::vec3( _width, _height, 0.0f),},
    },
    indices {
        0, 1, 2, 3,
    } {
    mesh_width = _width;
    mesh_height = _height;

    this->textures = textures;
    setupMesh(); 
}
void TerrainMesh::Draw(Shader const &shader) const {
    if (shader.hasTes == false) {
        throw "TERMESH: tess shaders required";
    }
    unsigned int normalNr   = 1;
    unsigned int heightNr   = 1;
    for(auto i = 0; i < textures.size(); i++) {
        string name;
        unsigned int number;
        glActiveTexture(GL_TEXTURE0 + i);
        switch (textures[i]._type) {
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

    glEnableVertexAttribArray(0); // Positions	
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(1); // Normals	
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    glEnableVertexAttribArray(2); // Texture coords	
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));
    glEnableVertexAttribArray(3); // Tangent
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tangent));
    glEnableVertexAttribArray(4); // Bitangent
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, bitangent));
    
    glBindVertexArray(0);
}
