#include "ResourceManager.hpp"

map<string, Shader>  ResourceManager::shaders  = { };
map<string, Texture> ResourceManager::textures = { };
map<string, BaseLight*> ResourceManager::lights = { };
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SHADER
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ResourceManager::loadVF(string const& shader_name, string const& shader_path) {
    string vert_shader = shader_path + ".vert.glsl";
    string frag_shader = shader_path + ".frag.glsl";
    Shader new_shader = Shader(vert_shader.c_str(), frag_shader.c_str());
    setShader(shader_name, new_shader);
}
void ResourceManager::loadVTTF(string const& shader_name, string const& shader_path) {
    string vert_shader = shader_path + ".vert.glsl";
    string tcss_shader = shader_path + ".tcss.glsl";
    string tess_shader = shader_path + ".tess.glsl";
    string frag_shader = shader_path + ".frag.glsl";
    Shader new_shader = Shader(vert_shader.c_str(), tcss_shader.c_str(), tess_shader.c_str(), frag_shader.c_str());
    setShader(shader_name, new_shader);
}
void ResourceManager::loadVGF(string const& shader_name, string const& shader_path) {
    string vert_shader = shader_path + ".vert.glsl";
    string geom_shader = shader_path + ".geom.glsl";
    string frag_shader = shader_path + ".frag.glsl";
    Shader new_shader = Shader(vert_shader.c_str() , geom_shader.c_str(), frag_shader.c_str());
    setShader(shader_name, new_shader);
}
void ResourceManager::loadVTTGF(string const& shader_name, string const& shader_path) {
    string vert_shader = shader_path + ".vert.glsl";
    string tcss_shader = shader_path + ".tcss.glsl";
    string tess_shader = shader_path + ".tess.glsl";
    string geom_shader = shader_path + ".geom.glsl";
    string frag_shader = shader_path + ".frag.glsl";
    Shader new_shader = Shader(vert_shader.c_str() , tcss_shader.c_str(), tess_shader.c_str(), geom_shader.c_str(), frag_shader.c_str());
    setShader(shader_name, new_shader);
}

void ResourceManager::setShader(string const& shader_name, Shader const& shader) {
    shaders.emplace(std::make_pair(shader_name, shader));
}

Shader ResourceManager::getShader(string const&shader_name) {
    auto _shader = shaders.find(shader_name);
    if (_shader == shaders.end()) {
        throw "Resource manager: shader not found";
    }
    return _shader->second;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TEXTURE
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ResourceManager::Load2D(string const &tex_name, string const &tex_path) {
    Texture texture;
    int width, height, nrChannels;
    unsigned char *data = stbi_load(tex_path.c_str(), &width, &height, &nrChannels, 0);
    if (data) {
        GLenum format;
        switch (nrChannels) {
            case 1: {format = GL_RED; break;}
            case 3: {format = GL_RGB; break;}
            case 4: {format = GL_RGBA; break;}
            default: throw "Resource manager: unknow color space";
        }
        texture._format = format;
        texture._path   = tex_path;
        texture.LoadTexture2D(width, height, data);
        stbi_image_free(data);
        setTexture(tex_name, texture);
    }
    else {
        stbi_image_free(data);
        throw "Resource manager: file "+ tex_path + " not exists";
    }
}

void ResourceManager::Load2DCube(string const &tex_name, vector<string> const &tex_faces) {
    int count = 0;
    for (auto &tex_path : tex_faces) {
        Texture texture;
        int width, height, nrChannels;
        unsigned char *data = stbi_load(tex_path.c_str(), &width, &height, &nrChannels, 0);
        if (data) {
            GLenum format;
            switch (nrChannels) {
                case 1: {format = GL_RED; break;}
                case 3: {format = GL_RGB; break;}
                case 4: {format = GL_RGBA; break;}
                default: throw "Resource manager: unknow color space";
            }
            texture._format = format;
            texture._path   = tex_path;
            texture.LoadTexture2D(width, height, data);
            stbi_image_free(data);
            setTexture(tex_name + "_" + std::to_string(count), texture);
        }
        else {
            stbi_image_free(data);
            throw "Resource manager: file "+ tex_path + " not exists";
        }
    }
}

void ResourceManager::Load2DDynamic(string const &tex_name, imap2d const &tex_map, int width, int height) {
    Texture texture;
    texture._format = GL_RED;
    texture._path   = "dynamic";
    float dynamic_data[width * height];
    for (auto i = 0; i < width; ++i) 
        memcpy(dynamic_data + i * height, tex_map[i].data(), height * sizeof(float));
    texture.LoadTexture2DFloat(width, height, dynamic_data);
    setTexture(tex_name, texture);
}

void ResourceManager::Load3D(string const &tex_name, vector<string> const &tex_faces) {
    int width, height, nrChannels;
    GLenum format;
    Texture texture;
    texture._filter_max = texture._filter_min = GL_LINEAR;
    texture._warpr = texture._warps = texture._warpt = GL_CLAMP_TO_EDGE;
    unsigned char *data[6];
    for (auto i = 0; i < 6; ++i) {
        data[i] = stbi_load(tex_faces[i].c_str(), &width, &height, &nrChannels, 0);
        if (data[i]) {
            switch (nrChannels) {
                case 1: {format = GL_RED; break;}
                case 3: {format = GL_RGB; break;}
                case 4: {format = GL_RGBA; break;}
                default: throw "Resource manager: unknow color space";
            }
        }
        else {
            stbi_image_free(data[i]);
            throw "Resource manager: file "+ tex_faces[i] + " not exists";
        }
    }
    texture._format = format;
    texture._path   = "cube";
    texture.LoadTexture3D(width, height, data);
    for (auto i = 0; i < 6; ++i) {
        stbi_image_free(data[i]);
    }
    setTexture(tex_name, texture);
}

void ResourceManager::setTexture(string const& tex_name, Texture const& tex) {
    textures.emplace(std::make_pair(tex_name, tex));
}

Texture ResourceManager::getTexture(string const&tex_name) {
    auto _tex = textures.find(tex_name);
    if (_tex == textures.end()) {
        throw "Resource manager: texture not found";
    }
    return _tex->second;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// LIGHT
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void ResourceManager::GenPLight(string const &light_name, int light_id, glm::vec3 const &light_pos, glm::vec3 const &light_color) {
    PLight* plight = new PLight(light_id);
    plight->setUpPLight(light_pos, light_color);
    lights.emplace(std::make_pair(light_name, plight));
}

void ResourceManager::GenALisht(string const &light_name, int light_id, glm::vec3 const &light_dir, glm::vec3 const &light_color) {
    ALight* alight = new ALight(light_id);
    alight->setUpALight(light_dir, light_color);
    lights.emplace(std::make_pair(light_name, alight));
}

BaseLight* ResourceManager::getLight(string const &light_name) {
    auto _light = lights.find(light_name);
    if (_light == lights.end()) {
        throw "Resource manager: light not found";
    }
    return _light->second;
}