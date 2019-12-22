#include "ShaderManager.hpp"
map<string, Shader> ShaderManager::shaders = {};

void ShaderManager::set(string shader_name, Shader const& shader) {
    shaders.emplace(std::make_pair(shader_name, shader));
}

Shader ShaderManager::get(string shader_name) {
    auto _shader = shaders.find(shader_name);
    if (_shader == shaders.end()) {
        throw "SHADER_M: shader not found";
    }
    return _shader->second;
}

void ShaderManager::loadVF(string const& shader_name, string const& shader_path) {
    string vert_shader = shader_path + ".vert.glsl";
    string frag_shader = shader_path + ".frag.glsl";
    Shader new_shader = Shader(vert_shader.c_str(), frag_shader.c_str());
    set(shader_name, new_shader);
}
void ShaderManager::loadVTTF(string const& shader_name, string const& shader_path) {
    string vert_shader = shader_path + ".vert.glsl";
    string tcss_shader = shader_path + ".tcss.glsl";
    string tess_shader = shader_path + ".tess.glsl";
    string frag_shader = shader_path + ".frag.glsl";
    Shader new_shader = Shader(vert_shader.c_str(), tcss_shader.c_str(), tess_shader.c_str(), frag_shader.c_str());
    set(shader_name, new_shader);
}
void ShaderManager::loadVGF(string const& shader_name, string const& shader_path) {
    string vert_shader = shader_path + ".vert.glsl";
    string geom_shader = shader_path + ".geom.glsl";
    string frag_shader = shader_path + ".frag.glsl";
    Shader new_shader = Shader(vert_shader.c_str() , geom_shader.c_str(), frag_shader.c_str());
    set(shader_name, new_shader);
}
void ShaderManager::loadVTTGF(string const& shader_name, string const& shader_path) {
    string vert_shader = shader_path + ".vert.glsl";
    string tcss_shader = shader_path + ".tcss.glsl";
    string tess_shader = shader_path + ".tess.glsl";
    string geom_shader = shader_path + ".geom.glsl";
    string frag_shader = shader_path + ".frag.glsl";
    Shader new_shader = Shader(vert_shader.c_str() , tcss_shader.c_str(), tess_shader.c_str(), geom_shader.c_str(), frag_shader.c_str());
    set(shader_name, new_shader);
}


