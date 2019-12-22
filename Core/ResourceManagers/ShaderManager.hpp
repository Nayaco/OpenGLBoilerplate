#ifndef SHADERMANAGER_HPP
#define SHADERMANAGER_HPP

#include "ResourceManager.hpp"
#include "Core/Graphics/Shader/Shader.hpp"

class ShaderManager {
private:
    static map<string, Shader> shaders;
public:
    static string name() {return "shader manager";}
    
    static void loadVF(string const& shader_name, string const& shader_path);
    static void loadVTTF(string const& shader_name, string const& shader_path);
    static void loadVGF(string const& shader_name, string const& shader_path);
    static void loadVTTGF(string const& shader_name, string const& shader_path);

    static void set(string shader_name, Shader const& shader);
    static Shader get(string shader_name);
};

#endif