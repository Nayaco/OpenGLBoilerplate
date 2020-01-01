#ifndef CLOUD_HPP
#define CLOUD_HPP

#include "Core/Common.hpp"
#include "Core/Context/Context.hpp"
#include "Core/Utility/Random.hpp"
#include "Core/Utility/Noise/Noise.hpp"
#include "Core/Context/Context.hpp"
#include "Core/Graphics/Shader/Shader.hpp"
#include "Core/Graphics/Texture/Texture.hpp"
#include "Core/Graphics/Mesh/TerrainMesh/TerrainMesh.hpp"
#include "Core/Graphics/Drawable.hpp"

class Cloud : public Renderable {
    enum class PLACEMENT: int {
        PLACEA = 0, PLACEB = 1, PLACEC = 2, PLACED = 3,
    };

    imap2d cloudmap[4];
    unsigned int attachments[6];
    int octave;
    float width, height;   
    float cloud_x, cloud_z;
    vertex_vector vertices;
    glm::vec2 wind_dir;
    Texture cloudmap_texture[4];
    float cloud_day_and_night;

    Shader cloud_shader;

    unsigned int VAO, VBO;
    unsigned int FBO;
    unsigned int RBO;
    
    virtual void setupMesh();
public:
    Texture cloud_tex;
    Cloud(Shader const &shader);

    virtual void initialize();
    virtual void setOctave(const int octave);
    virtual void generate();
    virtual void recycle();
    virtual void update(float delta_time, float day_and_night);

    virtual void render() const override;
    virtual void bind();
    virtual void unbind();
    virtual void destroy();
};

#endif