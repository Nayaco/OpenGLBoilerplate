#include "TextureManager.hpp"

map<string, Texture> TextureManager::textures = { };
map<string, imap2d>  TextureManager::heightmaps = { };

void TextureManager::Load2D(string const &tex_name, string const &tex_path, TEX_TYPE type) {
    Texture new_tex;
    new_tex.LoadTexture(tex_path, type);
    set(tex_name, new_tex);
    if (type == TEX_TYPE::HEIGHTMAP) {
        int width, height, nrChannels;
        unsigned char *data = stbi_load(tex_path.c_str(), &width, &height, &nrChannels, 0);
        imap2d new_map2(width);
        for (auto i = 0; i < width; ++i) {
            new_map2[i].reserve(height);
            for (auto j = 0; j < height; ++j) {
                new_map2[i][j] = ((float)data[i * height + j]) / 255.0f;
            }
        }
        stbi_image_free(data);
        set(tex_name, new_map2);
    }
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

void TextureManager::set(string tex_name, imap2d const& heightmap) {
    heightmaps.emplace(std::make_pair(tex_name, heightmap));
}

Texture TextureManager::get(string tex_name) {
    auto _tex = textures.find(tex_name);
    if (_tex == textures.end()) {
        throw "TEX_M: texture not found";
    }
    return _tex->second;
}

imap2d& TextureManager::getHeightMap(string tex_name) {
    auto _hm = heightmaps.find(tex_name);
    if (_hm == heightmaps.end()) {
        throw "TEX_M: heightmap not found";
    }
    return _hm->second;
}