#include "Skybox.hpp"

Skybox::Skybox(Texture texture)
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
        0, 2, 1, 0, 3, 2,
        4, 5, 6, 4, 6, 7,
        2, 3, 6, 3, 6, 7,
        0, 1, 5, 0, 4, 5,
        0, 3, 4, 3, 4, 7,
        1, 2, 5, 2, 5, 6,
    } {
    this->texture = texture;
    sky_color = glm::vec3(1.0f);
    setupMesh();
}

Skybox::~Skybox() { }

void Skybox::setColor(glm::vec3 color) {
    sky_color = color;
}
void Skybox::draw(Shader const &shader) const {
    glDepthFunc(GL_LEQUAL);
    texture.bind();

    shader.setInt("texture_cube_0", 0);
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