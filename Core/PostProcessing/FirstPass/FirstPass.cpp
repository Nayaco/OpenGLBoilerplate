#include "FirstPass.hpp"

FirstPass::FirstPass(unsigned int width, unsigned int height, bool bloomon, float exposure)
    :width(width), height(height), bloomOn(bloomon), exposure(exposure),
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
    setupMesh();
}

void FirstPass::draw(const Shader &shader) const {
    shader.use();
    shader.setInt("bloom", bloomOn);
    shader.setFloat("exposure", exposure);
    shader.setInt("scene", 0);
    shader.setInt("bloomBlur", 1);
    shader.setInt("clouding", 2);
    
    for (auto i = 0; i < 3; i++) {
        glActiveTexture(GL_TEXTURE0 + i);
        texture_render[i].bind();
    }
    
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
}

void FirstPass::bind() const {
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void FirstPass::unbind() const {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void FirstPass::initialize() {
    glGenFramebuffers(1, &FBO);
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);
    for (auto i = 0; i < 3; i++) {
        texture_buffers[i].GenPostProcessMap(width, height);
        texture_render[i] = texture_buffers[i];
        glFramebufferTexture2D(
            GL_FRAMEBUFFER,
            GL_COLOR_ATTACHMENT0 + i,
            GL_TEXTURE_2D,
            texture_buffers[i]._id, 0);
    }

    glGenRenderbuffers(1, &RBO);
    glBindRenderbuffer(GL_RENDERBUFFER, RBO);
    glRenderbufferStorage(GL_RENDERBUFFER, 
                        GL_DEPTH_COMPONENT, 
                        width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, 
                        GL_DEPTH_ATTACHMENT, 
                        GL_RENDERBUFFER, RBO);
    glDrawBuffers(3, attachments);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        throw "FIRSTPASS: framebuffer no complete";

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FirstPass::bindTexture(
    Texture const &firstpass_input_texture, unsigned int texture_order) {
    texture_render[texture_order] = firstpass_input_texture;
}

void FirstPass::setSize(unsigned int width, unsigned int height) {
    this->width = width;
    this->height = height;
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);
    for (auto i = 0; i < 3; i++) {
        texture_buffers[i].destroy();
        texture_buffers[i].GenPostProcessMap(width, height);
        texture_render[i] = texture_buffers[i];
        glFramebufferTexture2D(
            GL_FRAMEBUFFER,
            GL_COLOR_ATTACHMENT0 + i,
            GL_TEXTURE_2D,
            texture_buffers[i]._id, 0);
    }
    glBindRenderbuffer(GL_RENDERBUFFER, RBO);
    glRenderbufferStorage(GL_RENDERBUFFER, 
                        GL_DEPTH_COMPONENT, 
                        width, height);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FirstPass::setupMesh() {
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