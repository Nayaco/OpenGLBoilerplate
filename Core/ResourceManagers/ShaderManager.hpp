#ifndef SHADERMANAGER_HPP
#define SHADERMANAGER_HPP

#include "ResourceManager.hpp"
#include "Core/Graphics/Shader/Shader.hpp"

class ShaderManager {
private:
    static map<string, Shader> shaders;
public:
    static string name() {return "shader manager";}
    static void set(string shader_name, Shader const& shader);
    static Shader get(string shader_name);
};

#endif