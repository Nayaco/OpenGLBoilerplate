#ifndef TEXTUREMANAGER_HPP
#define TEXTUREMANAGER_HPP

#include "ResourceManager.hpp"
#include "Core/Graphics/Texture/Texture.hpp"
#include "Core/Utility/Noise/Noise.hpp"

class TextureManager {
private:
    static map<string, Texture> textures;
    static map<string, imap2d>  heightmaps;
public:
    static string name() {return "texture manager";}
    
    static void Load2D(string const &tex_name, string const &tex_path, TEX_TYPE type = TEX_TYPE::DEFAULT);
    static void Load2DCube(string const &tex_name, vector<string> const &tex_faces);
    static void Load2DDynamic(string const &tex_name, imap2d const &tex_map, int width, int height);

    static void set(string tex_name, Texture const& tex);
    static void set(string tex_name, imap2d const& heightmap);
    static Texture get(string tex_name);
    static imap2d& getHeightMap(string tex_name);
};

#endif