#include "Font.hpp"

Font::Font(Shader const& shader):fontshader(shader) { }

void Font::initialize(float width, float height) {
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); 
    for (auto c = 0; c < 128; c++) {
        FT_Face face = ResourceManager::loadChar(c);
        Texture tex; tex._type = tex._format = GL_RED;
        tex._warps = tex._warpt = GL_CLAMP_TO_EDGE;
        tex.LoadTexture2D(
            face->glyph->bitmap.width, 
            face->glyph->bitmap.rows,
            face->glyph->bitmap.buffer);
        characters.insert(std::make_pair(c, Character {
            texture: tex,
            Size: glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            Bearing: glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            Advance: face->glyph->advance.x,
        }) );
    }
    ResourceManager::destroyFont();
    
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    fontshader.use();
    fontshader.setMat4("projection", glm::ortho(0.0f, static_cast<GLfloat>(width), 0.0f, static_cast<GLfloat>(height)) );
}

void Font::update(float width, float height) {
    fontshader.use();
    fontshader.setMat4("projection", glm::ortho(0.0f, static_cast<GLfloat>(width), 0.0f, static_cast<GLfloat>(height)) );
}

void Font::renderText(string text, float x, float y, float scale, glm::vec3 color) {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    fontshader.use();
    fontshader.setVec3("textColor", color);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(VAO);

    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++) 
    {
        Character ch = characters[*c];

        float xpos = x + ch.Bearing.x * scale;
        float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

        float w = ch.Size.x * scale;
        float h = ch.Size.y * scale;
        float vertices[6][4] = {
            { xpos,     ypos + h,   0.0, 0.0 },            
            { xpos,     ypos,       0.0, 1.0 },
            { xpos + w, ypos,       1.0, 1.0 },

            { xpos,     ypos + h,   0.0, 0.0 },
            { xpos + w, ypos,       1.0, 1.0 },
            { xpos + w, ypos + h,   1.0, 0.0 }           
        };
        ch.texture.bind();
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // Be sure to use glBufferSubData and not glBufferData

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        x += (ch.Advance >> 6) * scale; 
    }
    glDisable(GL_BLEND);
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}
