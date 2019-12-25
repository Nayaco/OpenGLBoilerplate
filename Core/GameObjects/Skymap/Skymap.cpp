#include "Skymap.hpp"

Skymap::Skymap() 
    :attachments{GL_COLOR_ATTACHMENT0, 
                GL_COLOR_ATTACHMENT1,
                GL_COLOR_ATTACHMENT2,
                GL_COLOR_ATTACHMENT3,
                GL_COLOR_ATTACHMENT4,
                GL_COLOR_ATTACHMENT5}, 
    skymap_shader("Resources/Shaders/SkyMap/skymap.vert.glsl", 
                "Resources/Shaders/SkyMap/skymap.frag.glsl"),
    vertices {
        Vertex {position:glm::vec3( 1.0f,  1.0f, -1.0f)},
        Vertex {position:glm::vec3( 1.0f, -1.0f, -1.0f)},
        Vertex {position:glm::vec3(-1.0f,  1.0f, -1.0f)},
        Vertex {position:glm::vec3(-1.0f,  1.0f, -1.0f)},
        Vertex {position:glm::vec3( 1.0f, -1.0f, -1.0f)},
        Vertex {position:glm::vec3(-1.0f, -1.0f, -1.0f)},
    }, 
    skymap_texture(6) {
    map_width = 800; map_height = 600;
    setupMesh();
}

void Skymap::initialize() {
    glGenFramebuffers(1, &FBO);
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);
    for (auto i = 0; i < 6; i++) {
        skymap_texture[i].GenPostProcessMap(map_width, map_height);
        glFramebufferTexture2D(
            GL_FRAMEBUFFER,
            GL_COLOR_ATTACHMENT0 + i,
            GL_TEXTURE_2D,
            skymap_texture[i]._id, 0);
    }
    // skymap_texture[0].GenPostProcessMap(map_width, map_height);
    // glFramebufferTexture2D(
    //         GL_FRAMEBUFFER,
    //         GL_COLOR_ATTACHMENT0,
    //         GL_TEXTURE_2D,
    //         skymap_texture[0]._id, 0);

    glGenRenderbuffers(1, &RBO);
    glBindRenderbuffer(GL_RENDERBUFFER, RBO);
    glRenderbufferStorage(GL_RENDERBUFFER, 
                        GL_DEPTH24_STENCIL8, 
                        map_width, map_height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, 
                        GL_DEPTH_STENCIL_ATTACHMENT, 
                        GL_RENDERBUFFER, RBO);
    glDrawBuffers(6, attachments);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        throw "SKYMAP: framebuffer no complete";
    glBindRenderbuffer(GL_FRAMEBUFFER, 0);
}

void Skymap::setupMesh() {
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

void Skymap::bind() {
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_CULL_FACE);
}

void Skymap::unbind() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClearColor(0.0f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_CULL_FACE);
}

void Skymap::render(glm::vec3 sun_pos, glm::vec3 sun_color) {
    skymap_shader.use();
    skymap_shader.setVec3("skymap_sun_pos", sun_pos);
    skymap_shader.setVec3("skymap_sun_color", sun_color);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}
