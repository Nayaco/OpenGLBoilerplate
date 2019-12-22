#include "TextureManager.hpp"

map<string, Texture> TextureManager::textures = { };

void TextureManager::Load2D(string const &tex_name, string const &tex_path, TEX_TYPE type) {
    Texture new_tex;
    new_tex.LoadTexture(tex_path, type);
    set(tex_name, new_tex);
}
void TextureManager::Load2DCube(string const &tex_name, vector<string> const &tex_faces) {
    Texture new_tex;
    new_tex.LoadCubemap(tex_faces);
    set(tex_name, new_tex);
}
void TextureManager::Load2DDynamic(string const &tex_name, imap2d const &tex_map, int width, int height) {
    Texture new_tex;
    new_tex.LoadFromImap2d(tex_map, width, height);
    set(tex_name, new_tex);
}

void TextureManager::set(string tex_name, Texture const& tex) {
    textures.emplace(std::make_pair(tex_name, tex));
}

Texture TextureManager::get(string tex_name) {
     auto _tex = textures.find(tex_name);
    if (_tex == textures.end()) {
        throw "TEX_M: texture not found";
    }
    return _tex->second;
}