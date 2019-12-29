#include "ParticleSystem.hpp"

int ParticleSystem::lastUsedParticle = 0;

ParticleSystem::ParticleSystem(Texture const &texture, int amount) 
: particle_texture(texture), amount(amount), vertices { 
    Vertex{position: glm::vec3(0.0f, 1.0f, 0.0f), normal: glm::vec3(0.0), texCoords: glm::vec2(0.0f, 1.0f)},//0 
    Vertex{position: glm::vec3(1.0f, 0.0f, 0.0f), normal: glm::vec3(0.0), texCoords: glm::vec2(1.0f, 0.0f)},//1
    Vertex{position: glm::vec3(0.0f, 0.0f, 0.0f), normal: glm::vec3(0.0), texCoords: glm::vec2(0.0f, 0.0f)},//2
    Vertex{position: glm::vec3(0.0f, 1.0f, 0.0f), normal: glm::vec3(0.0), texCoords: glm::vec2(0.0f, 1.0f)},//3
    Vertex{position: glm::vec3(1.0f, 1.0f, 0.0f), normal: glm::vec3(0.0), texCoords: glm::vec2(1.0f, 1.0f)},//4
    Vertex{position: glm::vec3(1.0f, 0.0f, 0.0f), normal: glm::vec3(0.0), texCoords: glm::vec2(1.0f, 0.0f)},//5
} { 
    setupMesh();
}

Particle ParticleSystem::newParticle() {
    Particle new_particle;
    float new_x = randomx::random(-0.1, 0.1);
    float new_y = randomx::random( 0.0, 0.1);
    float new_z = randomx::random(-0.1, 0.1);
    
    float new_x_vel = randomx::random(-0.5, 0.5);
    float new_y_vel = randomx::random(0.0, 1.0);
    float new_z_vel = randomx::random(-0.5, 0.5);
    glm::vec3 vel = 
        glm::normalize(glm::vec3(new_x_vel, new_y_vel, new_z_vel)) 
        * randomx::random(particle_source.minSpeed, particle_source.maxSpeed);
    
    new_particle.position = 
        particle_source.position + glm::vec3(new_x, new_y, new_z);
    new_particle.velocity = vel;
    new_particle.maxLifetime = 
        new_particle.lifetime = 
        randomx::random(particle_source.minLifetime, particle_source.maxLifetime);
    return new_particle;
}

void ParticleSystem::respawn(Particle &particle) {
    particle = newParticle();
}

int ParticleSystem::firstUnusedParticle() {
    for (auto i = lastUsedParticle; i < amount; ++i) {
        if(particles[i].lifetime <= 0.0) {
            lastUsedParticle = i;
            return i;
        }
    }
    for (auto i = 0; i < lastUsedParticle; ++i) {
        if(particles[i].lifetime <= 0.0) {
            lastUsedParticle = i;
            return i;
        }
    }
    lastUsedParticle = 0;
    return 0;
}

void ParticleSystem::initialize(glm::vec3 pos, glm::vec3 accelerate, 
    float minspeed, float maxspeed, 
    float minlife, float maxlife) {
    setGenerator(pos, accelerate, minspeed, maxspeed, minlife, maxlife);

    for (auto i = 0; i < amount; ++i) {
        particles.push_back(Particle {
            position: glm::vec3(0.0), 
            velocity: glm::vec3(0.0), 
            alpha: 0.0, 
            size: 0.0, 
            lifetime: 0.0, 
            maxLifetime: maxlife, 
        });
    }
}

void ParticleSystem::setGenerator(glm::vec3 pos, glm::vec3 accelerate, 
        float minspeed, float maxspeed, 
        float minlife, float maxlife) {
    particle_source.maxLifetime = maxlife; 
    particle_source.minLifetime = minlife;
    particle_source.minSpeed = minspeed;
    particle_source.maxSpeed = maxspeed;
    particle_source.position = pos;
    particle_source.acceleration = accelerate;
}
void ParticleSystem::update(float delta_time, int new_particles) {
    for (auto i = 0; i < new_particles; ++i) {
        int unused = firstUnusedParticle();
        respawn(particles[unused]);
    }

    for (auto &p : particles) {
        p.lifetime -= delta_time;
        if (p.lifetime > 0.0) {
            p.position += p.velocity * delta_time;
            p.velocity += particle_source.acceleration * delta_time;
            float factor = powf((p.lifetime / p.maxLifetime), 2.0);
                // 1.0f / ((p.lifetime / p.maxLifetime) * (p.lifetime / p.maxLifetime) + 1.0);
            p.alpha = factor;
            p.size = 0.17f * factor;
        }
    }
}

void ParticleSystem::draw(Shader const &shader) const {
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    shader.use();
    particle_texture.bind();
    glBindVertexArray(VAO);
    for (auto &p : particles) {
        if (p.lifetime > 0.0) {
            shader.setVec3("offset", p.position);
            shader.setFloat("alpha", p.alpha);
            shader.setFloat("scale", p.size);
            glDrawArrays(GL_TRIANGLES, 0, 6);
        }
    }
    glBindVertexArray(0);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void ParticleSystem::setupMesh() {
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

