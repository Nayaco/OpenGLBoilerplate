#ifndef FONT_HPP
#define FONT_HPP

#include "Core/Common.hpp"
#include "Core/Graphics/Texture/Texture.hpp"
#include "Core/Graphics/Shader/Shader.hpp"
#include "Core/ResourceManager/ResourceManager.hpp"
struct Character {
    Texture texture;   
    glm::ivec2 Size;    
    glm::ivec2 Bearing; 
    unsigned int Advance;    
};

class Font {
    unsigned int VAO;
    unsigned int VBO;
    map<char, Character> characters;
    Shader fontshader; 
    glm::mat4 projection_matrix;

public:
    Font(Shader const& shader);
    void initialize(float width, float height);
    void update(float width, float height);
    void renderText(string text, float x, float y, float scale, glm::vec3 color);
};


#endif