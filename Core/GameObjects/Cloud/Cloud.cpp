#include "Cloud.hpp"

Cloud::Cloud(Shader const &shader) :
    attachments{GL_COLOR_ATTACHMENT0, 
                GL_COLOR_ATTACHMENT1,
                GL_COLOR_ATTACHMENT2,
                GL_COLOR_ATTACHMENT3,
                GL_COLOR_ATTACHMENT4,
                GL_COLOR_ATTACHMENT5}, 
    vertices {
        Vertex {position:glm::vec3(-1.0,  1.0, 0.0), normal:glm::vec3(0.0), texCoords:glm::vec2(0.0, 1.0)},
        Vertex {position:glm::vec3(-1.0, -1.0, 0.0), normal:glm::vec3(0.0), texCoords:glm::vec2(0.0, 0.0)},
        Vertex {position:glm::vec3( 1.0,  1.0, 0.0), normal:glm::vec3(0.0), texCoords:glm::vec2(1.0, 1.0)},
        Vertex {position:glm::vec3( 1.0, -1.0, 0.0), normal:glm::vec3(0.0), texCoords:glm::vec2(1.0, 0.0)},
    }, cloud_shader(shader) {
    width = height = 1600.0;
    cloud_x = cloud_z = 0.0;
    octave = 12;
    wind_dir = glm::normalize(glm::vec2(1.0, 2.0));
    setupMesh();
    cloud_day_and_night = 1.0;
}

void Cloud::setupMesh() {
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

void Cloud::initialize() {
    glGenFramebuffers(1, &FBO);
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);
    
    cloud_tex.GenPostProcessMap(width, height);
    glFramebufferTexture2D(
        GL_FRAMEBUFFER,
        GL_COLOR_ATTACHMENT0,
        GL_TEXTURE_2D,
        cloud_tex._id, 0);

    glGenRenderbuffers(1, &RBO);
    glBindRenderbuffer(GL_RENDERBUFFER, RBO);
    glRenderbufferStorage(GL_RENDERBUFFER, 
                        GL_DEPTH24_STENCIL8, 
                        width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, 
                        GL_DEPTH_STENCIL_ATTACHMENT, 
                        GL_RENDERBUFFER, RBO);
    glDrawBuffers(1, attachments);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        throw "SKYMAP: framebuffer no complete";
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Cloud::bind() {
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glDisable(GL_CULL_FACE);
    glViewport(0, 0, width, height);
}

void Cloud::unbind() {
    glViewport(0, 0, Context::window_width, Context::window_height);
    glEnable(GL_CULL_FACE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Cloud::update(float delta_time, float day_and_night) {
    cloud_x += delta_time * wind_dir.x * 0.02;
    cloud_z += delta_time * wind_dir.y * 0.02;
    cloud_day_and_night = day_and_night;
    recycle();
}

void Cloud::recycle() { 
    if (cloud_x >= 0.5) {
        Texture tempA = cloudmap_texture[(int)PLACEMENT::PLACEA];
        Texture tempC = cloudmap_texture[(int)PLACEMENT::PLACEC];
        cloudmap_texture[(int)PLACEMENT::PLACEA] = cloudmap_texture[(int)PLACEMENT::PLACEB];
        cloudmap_texture[(int)PLACEMENT::PLACEC] = cloudmap_texture[(int)PLACEMENT::PLACED];
        cloudmap_texture[(int)PLACEMENT::PLACEB] = tempA;
        cloudmap_texture[(int)PLACEMENT::PLACED] = tempC;
        cloud_x -= 1.0;
    } else if (cloud_x <= -0.5) {
        Texture tempA = cloudmap_texture[(int)PLACEMENT::PLACEA];
        Texture tempC = cloudmap_texture[(int)PLACEMENT::PLACEC];
        cloudmap_texture[(int)PLACEMENT::PLACEA] = cloudmap_texture[(int)PLACEMENT::PLACEB];
        cloudmap_texture[(int)PLACEMENT::PLACEC] = cloudmap_texture[(int)PLACEMENT::PLACED];
        cloudmap_texture[(int)PLACEMENT::PLACEB] = tempA;
        cloudmap_texture[(int)PLACEMENT::PLACED] = tempC;
        cloud_x += 1.0;
    }
    if (cloud_z >= 0.5) {
        Texture tempA = cloudmap_texture[(int)PLACEMENT::PLACEA];
        Texture tempB = cloudmap_texture[(int)PLACEMENT::PLACEB];
        cloudmap_texture[(int)PLACEMENT::PLACEA] = cloudmap_texture[(int)PLACEMENT::PLACEC];
        cloudmap_texture[(int)PLACEMENT::PLACEB] = cloudmap_texture[(int)PLACEMENT::PLACED];
        cloudmap_texture[(int)PLACEMENT::PLACEC] = tempA;
        cloudmap_texture[(int)PLACEMENT::PLACED] = tempB;
        cloud_z -= 1.0;
    } else if (cloud_z <= -0.5) {
        Texture tempA = cloudmap_texture[(int)PLACEMENT::PLACEA];
        Texture tempB = cloudmap_texture[(int)PLACEMENT::PLACEB];
        cloudmap_texture[(int)PLACEMENT::PLACEA] = cloudmap_texture[(int)PLACEMENT::PLACEC];
        cloudmap_texture[(int)PLACEMENT::PLACEB] = cloudmap_texture[(int)PLACEMENT::PLACED];
        cloudmap_texture[(int)PLACEMENT::PLACEC] = tempA;
        cloudmap_texture[(int)PLACEMENT::PLACED] = tempB;
        cloud_z += 1.0;
    }    
}

void Cloud::render() const {
    cloud_shader.use();
    cloud_shader.setInt("cloud_textureA", 0);
    cloud_shader.setInt("cloud_textureB", 1);
    cloud_shader.setInt("cloud_textureC", 2);
    cloud_shader.setInt("cloud_textureD", 3);

    cloud_shader.setFloat("offset_x", cloud_x);
    cloud_shader.setFloat("offset_z", cloud_z);    
    cloud_shader.setFloat("day_and_night", cloud_day_and_night);
    
    glActiveTexture(GL_TEXTURE0);
    cloudmap_texture[0].bind();
    glActiveTexture(GL_TEXTURE1);
    cloudmap_texture[1].bind();
    glActiveTexture(GL_TEXTURE2);
    cloudmap_texture[2].bind();
    glActiveTexture(GL_TEXTURE3);
    cloudmap_texture[3].bind();
    
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
}

void Cloud::setOctave(const int octave) { this->octave = octave; }

static glm::vec2 cut_map[] = {
    glm::vec2(0, 0), glm::vec2(0, 1),
    glm::vec2(1, 0), glm::vec2(1, 1),
};


void Cloud::generate() {
    unsigned char data[(int)(width * height * 3)];
    imap2d originmap = noise::perlNoise(noise::whiteNoise(width * 2, height * 2), 
        octave, width * 2, height * 2);
    float maxH = 0.0;
    for (int i = 0; i < 2 * width; i++) {
        for (int j = 0; j < 2 * height; j++) {
            maxH = glm::max(maxH, originmap[i][j]);
        }
    }
    for (int i = 0; i < 2 * width; i++) {
        for (int j = 0; j < 2 * height; j++) {
            originmap[i][j] /= maxH;
        }
    }    
    for (auto texture_order = 0; texture_order < 4; texture_order++) {
        glm::vec2 offset = cut_map[texture_order];
        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                data[i * (int)height * 3 + j * 3 + 2] =
                data[i * (int)height * 3 + j * 3 + 1] = 
                data[i * (int)height * 3 + j * 3] = 
                    (unsigned char)(originmap[i + width * offset.x][j + height * offset.y] * 255);
            }

        } 
        cloudmap_texture[texture_order]._format = cloudmap_texture[texture_order]._type = GL_RGB;
        cloudmap_texture[texture_order]._warps = cloudmap_texture[texture_order]._warpt = GL_CLAMP_TO_EDGE;
        cloudmap_texture[texture_order].LoadTexture2D(width, height, data);
    }
}

void Cloud::destroy() { }