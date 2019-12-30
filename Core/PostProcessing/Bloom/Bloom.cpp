#include "Bloom.hpp"

Bloom::Bloom(unsigned int width, unsigned int height)
    :width(width), height(height),
    attachments{GL_COLOR_ATTACHMENT0, 
                GL_COLOR_ATTACHMENT1,
                GL_COLOR_ATTACHMENT2,
                GL_COLOR_ATTACHMENT3,
                GL_COLOR_ATTACHMENT4,
                GL_COLOR_ATTACHMENT5}, 
    vertices {
        Vertex {position:glm::vec3(-1.0f,  1.0, 0.0), normal:glm::vec3(0.0), texCoords:glm::vec2(0.0, 1.0)},
        Vertex {position:glm::vec3(-1.0f, -1.0, 0.0), normal:glm::vec3(0.0), texCoords:glm::vec2(0.0, 0.0)},
        Vertex {position:glm::vec3( 1.0f,  1.0, 0.0), normal:glm::vec3(0.0), texCoords:glm::vec2(1.0, 1.0)},
        Vertex {position:glm::vec3( 1.0f, -1.0, 0.0), normal:glm::vec3(0.0), texCoords:glm::vec2(1.0, 0.0)},
    } {
    blur_amount = 10;
    horizon = blur_amount & 0x1;
    setupMesh();
}

void Bloom::setupMesh() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);  
    
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

void Bloom::initialize() {
    glGenFramebuffers(2, FBO);
    for (auto i = 0; i < 2; i++) {
        glBindFramebuffer(GL_FRAMEBUFFER, FBO[i]);
        bloom_textures[i].GenPostProcessMap(width, height);
        glFramebufferTexture2D(
            GL_FRAMEBUFFER,
            GL_COLOR_ATTACHMENT0,
            GL_TEXTURE_2D,
            bloom_textures[i]._id, 0);
        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            throw "BLOOM: framebuffer no complete";
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Bloom::setSize(unsigned int width, unsigned int height) {
    this->width = width;
    this->height = height;
    for (auto i = 0; i < 2; i++) {
        bloom_textures[i].destroy();
        glBindFramebuffer(GL_FRAMEBUFFER, FBO[i]);
        bloom_textures[i].GenPostProcessMap(width, height);
        glFramebufferTexture2D(
            GL_FRAMEBUFFER,
            GL_COLOR_ATTACHMENT0,
            GL_TEXTURE_2D,
            bloom_textures[i]._id, 0);
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Bloom::bindTexture(Texture const &bloom_origin) {
    this->bloom_origin = bloom_origin;
}

void Bloom::draw(const Shader &shader) const { 
    bool horizontal = true, first_iteration = true;
    shader.use();
    shader.setInt("bloom_origin", 0);
    glActiveTexture(GL_TEXTURE0);
    for (auto i = 0; i < blur_amount; i++) {
        glBindFramebuffer(GL_FRAMEBUFFER, FBO[horizontal]);
        shader.setInt("horizontal", horizontal);
        if (!first_iteration) {
            bloom_textures[!horizontal].bind();
        } else {
            bloom_origin.bind();
        }
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        horizontal = !horizontal;
        first_iteration = false;
    }
    glBindVertexArray(0);
}

void Bloom::bind() const {  }

void Bloom::unbind() const {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
