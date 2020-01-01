#ifndef RENDERENGINE_GRASSBLADE_H
#define RENDERENGINE_GRASSBLADE_H

#include "Core/Common.hpp"
#include "Core/Graphics/Shader/Shader.hpp"
// #include <Utility/GrassUtils/FloatTexture.hpp>
#include "Core/Utility/GrassUtils/FloatTexture.hpp"
#include "Core/Utility/GrassUtils/NoiseGen.hpp"
#include "Core/Utility/GrassUtils/Transform.hpp"
// #include "../Utils/NoiseGen.hpp"
#include "GrassElement.hpp"

class GrassBlade {
public:
    GrassBlade(glm::vec3 _scale, glm::vec3 center, glm::vec2 size, float density, Shader const& shader);

    void render();
    void setLightPos(glm::vec3 position);
    void setCameraPos(glm::vec3 position);
    void setViewMatrix(glm::mat4x4 view);
    void setProjectionMatrix(glm::mat4x4 projection);
private:
    static GLfloat vertices[];
    static GLint indices[];
    static GLfloat normals[];
    static GLfloat texCoord[];
    GLuint VAO;
    GLuint VBO_Pos;
    GLuint VBO_Norm;
    Shader grassShader;

    void initBuffers();
    void setupShader();
    
    //Plane_sine *plane_sine;
    NoiseGen noise_gen;
    FloatTexture tex_wind_noise;
 
    uint grassNumber;
    glm::vec3 camera_position;
    glm::vec3 light_position;
 
    float wind_dir[2];
 
    glm::mat4 view_matrix;
    glm::mat4 projection_matrix;
 
    GLuint _tex_grass;
    GLuint _tex_wind_noise;
 
    std::vector<glm::mat4x4> modelMats;
};


#endif //RENDERENGINE_GRASSBLADE_HPP