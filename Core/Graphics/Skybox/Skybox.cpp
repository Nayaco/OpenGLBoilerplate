#include "Skybox.hpp"

Skybox::Skybox(texture_vector textures)
    :vertices { 
        Vertex{position: glm::vec3( 1.0f, 1.0f, 1.0f),},
        Vertex{position: glm::vec3( 1.0f, 1.0f,-1.0f),},
        Vertex{position: glm::vec3(-1.0f, 1.0f,-1.0f),},
        Vertex{position: glm::vec3(-1.0f, 1.0f, 1.0f),},
        Vertex{position: glm::vec3( 1.0f,-1.0f, 1.0f),},
        Vertex{position: glm::vec3( 1.0f,-1.0f,-1.0f),},
        Vertex{position: glm::vec3(-1.0f,-1.0f,-1.0f),},
        Vertex{position: glm::vec3(-1.0f, 1.0f, 1.0f),},
    },
    indices {
        0, 2, 1,
        0, 3, 2,
        
        4, 5, 6,
        4, 6, 7,

        2, 3, 6,
        3, 6, 7,
        
        0, 1, 5,
        0, 4, 5,

        0, 3, 4,
        3, 4, 7,

        1, 2, 5,
        2, 5, 6,
    } {
    this->textures = textures;
    sky_color = glm::vec3(1.0f);
    setupMesh();
}

Skybox::~Skybox() { }

void Skybox::setColor(glm::vec3 color) {
    sky_color = color;
}
void Skybox::draw(Shader const &shader) const {
    glDepthFunc(GL_LEQUAL);
    if (textures.size() < 1) {
        throw "SKYBOX: should have a cube texture";
    } 
    for(size_t i = 0; i < textures.size(); i++) {
        string name;
        unsigned int number;
        glActiveTexture(GL_TEXTURE0 + i);
        switch (textures[i]._type) {
            case TEX_TYPE::CUBEMAP:     {name = "texture_cube"; number = 0; break;}
            default: {throw "SKYBOX: texture type unusable";}
        }
        shader.setInt(name + "_" + std::to_string(number), i);
        textures[i].bind();
    }
    shader.setVec3("sky_color", sky_color);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    glActiveTexture(GL_TEXTURE0);
    glDepthFunc(GL_LESS);
}

void Skybox::setupMesh() {
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