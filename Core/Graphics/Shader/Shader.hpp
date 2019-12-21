#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
using std::string;
class Shader {
public:
    unsigned int ID;
    bool hasTes;
    bool hasGeo;
    Shader(const char* vertexPath, const char* fragmentPath);
    Shader(const char* vertexPath, const char* geoPath, const char* fragmentPath);
    Shader(const char* vertexPath, const char* tcsPath, const char* tesPath, const char* fragmentPath);
    Shader(const char* vertexPath, const char* tcsPath, const char* tesPath, const char* geoPath, const char* fragmentPath);
    
    void use() const { 
        glUseProgram(ID); 
    }

    void setBool(const string &name, bool value) const {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value); 
    }
    void setInt(const string &name, int value) const { 
        glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
    }
    void setFloat(const string &name, float value) const { 
        glUniform1f(glGetUniformLocation(ID, name.c_str()), value); 
    }
    void setVec2(const string &name, const glm::vec2 &value) const { 
        glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]); 
    }
    void setVec2(const string &name, float x, float y) const { 
        glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y); 
    }
    void setVec3(const string &name, const glm::vec3 &value) const { 
        glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]); 
    }
    void setVec3(const string &name, float x, float y, float z) const { 
        glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z); 
    }
    void setVec4(const string &name, const glm::vec4 &value) const { 
        glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]); 
    }
    void setVec4(const string &name, float x, float y, float z, float w) const { 
        glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w); 
    }
    void setMat2(const string &name, const glm::mat2 &mat) const {
        glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
    void setMat3(const string &name, const glm::mat3 &mat) const {
        glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
    void setMat4(const string &name, const glm::mat4 &mat) const {
        glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
private:
    void checkCompileErrors(GLuint shader, string type);
};

#endif