#include "Skybox.hpp"

Skybox::Skybox(Texture texture)
    :vertices { 
        Vertex{position: glm::vec3( 1.0f, 1.0f, 1.0f)},//0 
        Vertex{position: glm::vec3( 1.0f, 1.0f,-1.0f)},//1
        Vertex{position: glm::vec3(-1.0f, 1.0f,-1.0f)},//2
        Vertex{position: glm::vec3(-1.0f, 1.0f, 1.0f)},//3
        Vertex{position: glm::vec3( 1.0f,-1.0f, 1.0f)},//4
        Vertex{position: glm::vec3( 1.0f,-1.0f,-1.0f)},//5
        Vertex{position: glm::vec3(-1.0f,-1.0f,-1.0f)},//6
        Vertex{position: glm::vec3(-1.0f,-1.0f, 1.0f)},//7
    },
    indices {
        0, 2, 1, 0, 3, 2, // up
        4, 5, 6, 4, 6, 7, // down
        2, 3, 6, 3, 7, 6, // left
        0, 1, 5, 0, 5, 4, // right
        0, 4, 3, 3, 4, 7, // back
        1, 2, 5, 2, 6, 5, // front
    }, skybox_shader("Resources/Shaders/Skybox/Skybox.vert.glsl", 
        "Resources/Shaders/Skybox/Skybox.frag.glsl"){
    use_cube_map = true;
    this->texture = texture;
    sky_color = glm::vec3(1.0f);
    setupMesh();
}


Skybox::Skybox(texture_vector cube)
    :vertices { 
        Vertex{position: glm::vec3( 1.0f, 1.0f, 1.0f), normal: glm::vec3(0.0, 1.0, 0.0)},//0 
        Vertex{position: glm::vec3(-1.0f, 1.0f,-1.0f), normal: glm::vec3(0.0, 1.0, 0.0)},//2
        Vertex{position: glm::vec3( 1.0f, 1.0f,-1.0f), normal: glm::vec3(0.0, 1.0, 0.0)},//1
        Vertex{position: glm::vec3( 1.0f, 1.0f, 1.0f), normal: glm::vec3(0.0, 1.0, 0.0)},//0 
        Vertex{position: glm::vec3(-1.0f, 1.0f, 1.0f), normal: glm::vec3(0.0, 1.0, 0.0)},//3
        Vertex{position: glm::vec3(-1.0f, 1.0f,-1.0f), normal: glm::vec3(0.0, 1.0, 0.0)},//2
        
        Vertex{position: glm::vec3( 1.0f,-1.0f, 1.0f), normal: glm::vec3(0.0,-1.0, 0.0)},//4
        Vertex{position: glm::vec3( 1.0f,-1.0f,-1.0f), normal: glm::vec3(0.0,-1.0, 0.0)},//5
        Vertex{position: glm::vec3(-1.0f,-1.0f,-1.0f), normal: glm::vec3(0.0,-1.0, 0.0)},//6
        Vertex{position: glm::vec3( 1.0f,-1.0f, 1.0f), normal: glm::vec3(0.0,-1.0, 0.0)},//4
        Vertex{position: glm::vec3(-1.0f,-1.0f,-1.0f), normal: glm::vec3(0.0,-1.0, 0.0)},//6
        Vertex{position: glm::vec3(-1.0f,-1.0f, 1.0f), normal: glm::vec3(0.0,-1.0, 0.0)},//7

        Vertex{position: glm::vec3(-1.0f, 1.0f,-1.0f), normal: glm::vec3(-1.0, 0.0, 0.0)},//2
        Vertex{position: glm::vec3(-1.0f, 1.0f, 1.0f), normal: glm::vec3(-1.0, 0.0, 0.0)},//3
        Vertex{position: glm::vec3(-1.0f,-1.0f,-1.0f), normal: glm::vec3(-1.0, 0.0, 0.0)},//6
        Vertex{position: glm::vec3(-1.0f, 1.0f, 1.0f), normal: glm::vec3(-1.0, 0.0, 0.0)},//3
        Vertex{position: glm::vec3(-1.0f,-1.0f, 1.0f), normal: glm::vec3(-1.0, 0.0, 0.0)},//7
        Vertex{position: glm::vec3(-1.0f,-1.0f,-1.0f), normal: glm::vec3(-1.0, 0.0, 0.0)},//6

        Vertex{position: glm::vec3( 1.0f, 1.0f, 1.0f), normal: glm::vec3(1.0, 0.0, 0.0)},//0 
        Vertex{position: glm::vec3( 1.0f, 1.0f,-1.0f), normal: glm::vec3(1.0, 0.0, 0.0)},//1
        Vertex{position: glm::vec3( 1.0f,-1.0f,-1.0f), normal: glm::vec3(1.0, 0.0, 0.0)},//5
        Vertex{position: glm::vec3( 1.0f, 1.0f, 1.0f), normal: glm::vec3(1.0, 0.0, 0.0)},//0 
        Vertex{position: glm::vec3( 1.0f,-1.0f,-1.0f), normal: glm::vec3(1.0, 0.0, 0.0)},//5
        Vertex{position: glm::vec3( 1.0f,-1.0f, 1.0f), normal: glm::vec3(1.0, 0.0, 0.0)},//4

        Vertex{position: glm::vec3( 1.0f, 1.0f, 1.0f), normal: glm::vec3(0.0, 0.0, 1.0)},//0 
        Vertex{position: glm::vec3( 1.0f,-1.0f, 1.0f), normal: glm::vec3(0.0, 0.0, 1.0)},//4
        Vertex{position: glm::vec3(-1.0f, 1.0f, 1.0f), normal: glm::vec3(0.0, 0.0, 1.0)},//3
        Vertex{position: glm::vec3(-1.0f, 1.0f, 1.0f), normal: glm::vec3(0.0, 0.0, 1.0)},//3
        Vertex{position: glm::vec3( 1.0f,-1.0f, 1.0f), normal: glm::vec3(0.0, 0.0, 1.0)},//4
        Vertex{position: glm::vec3(-1.0f,-1.0f, 1.0f), normal: glm::vec3(0.0, 0.0, 1.0)},//7

        Vertex{position: glm::vec3( 1.0f, 1.0f,-1.0f), normal: glm::vec3(0.0, 0.0, -1.0)},//1
        Vertex{position: glm::vec3(-1.0f, 1.0f,-1.0f), normal: glm::vec3(0.0, 0.0, -1.0)},//2
        Vertex{position: glm::vec3( 1.0f,-1.0f,-1.0f), normal: glm::vec3(0.0, 0.0, -1.0)},//5
        Vertex{position: glm::vec3(-1.0f, 1.0f,-1.0f), normal: glm::vec3(0.0, 0.0, -1.0)},//2
        Vertex{position: glm::vec3(-1.0f,-1.0f,-1.0f), normal: glm::vec3(0.0, 0.0, -1.0)},//6
        Vertex{position: glm::vec3( 1.0f,-1.0f,-1.0f), normal: glm::vec3(0.0, 0.0, -1.0)},//5
    },
    skybox_shader("Resources/Shaders/Skybox/Skybox.vert.glsl", 
                "Resources/Shaders/Skybox/Skybox.frag.glsl"),
    skybox_textures(cube) {
    sky_color = glm::vec3(1.0f);
    use_cube_map = false;
    setupMesh();
}

Skybox::~Skybox() { }

void Skybox::setColor(glm::vec3 color) { sky_color = color; }

void Skybox::draw() const {
    glDepthFunc(GL_LEQUAL);

    skybox_shader.setInt("texture_skymap_rt", 0);
    skybox_shader.setInt("texture_skymap_lf", 1);
    skybox_shader.setInt("texture_skymap_up", 2);
    skybox_shader.setInt("texture_skymap_dn", 3);
    skybox_shader.setInt("texture_skymap_ft", 4);
    skybox_shader.setInt("texture_skymap_bk", 5);

    for (auto i = 0; i < 6; ++i) {
        glActiveTexture(GL_TEXTURE0 + i);
        skybox_textures[i].bind();
    }
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    
    glBindVertexArray(0);
    glActiveTexture(GL_TEXTURE0);
    glDepthFunc(GL_LESS);
}

void Skybox::draw(Shader const &shader) const {
    glDepthFunc(GL_LEQUAL);

    glActiveTexture(GL_TEXTURE0);
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
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);  
    
    if(use_cube_map) {
        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
    }
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