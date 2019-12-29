#ifndef PARTICLESYSTEM_HPP
#define PARTICLESYSTEM_HPP

#include "Core/Common.hpp"
#include "Core/Graphics/Drawable.hpp"
#include "Core/Graphics/Mesh/BaseMesh.hpp"
#include "Core/Graphics/Texture/Texture.hpp"
#include "Core/Graphics/Shader/Shader.hpp"
struct Particle {
    glm::vec3 position;
    glm::vec3 velocity;
    float  alpha;
    float  size;
    float  lifetime;
    float  maxLifetime;
};

struct Generator {
    float minSpeed, maxSpeed, r;
    float minLifetime, maxLifetime;
    glm::vec3 position;
    glm::vec3 acceleration;
};

class ParticleSystem : public Drawable {
    static   int    lastUsedParticle;
    unsigned int    VAO;
    unsigned int    VBO;
    vertex_vector   vertices;
    Texture         particle_texture;
    int             amount;
    Generator       particle_source;
    std::vector<Particle> particles;
    
    virtual Particle newParticle();
    virtual void respawn(Particle &particle);
    virtual int  firstUnusedParticle();
    virtual void setupMesh();
public:
    ParticleSystem(Texture const &texture, int amount);
    virtual void initialize(
        glm::vec3 pos, glm::vec3 accelerate, 
        float minspeed, float maxspeed, 
        float minlife, float maxlife);
    virtual void setGenerator(
        glm::vec3 pos, glm::vec3 accelerate, 
        float minspeed, float maxspeed, 
        float minlife, float maxlife);
    virtual void update(float delta_time, int new_particles);
    virtual void draw(Shader const &shader) const override;
};


#endif