#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <stb_image.h>
#include "Core/Common.hpp"

enum class TEX_TYPE: int8_t {
    DEFAULT    = 0,
    CUBEMAP    = 1,

    DIFFUSEMAP = 10,
    SPECULARMAP= 11,
    NORMALMAP  = 12,
    HEIGHTMAP  = 13,
};

struct Texture {
    unsigned int _id;
    TEX_TYPE     _type;
    string       _path;
    bool         _isGamma;
    unsigned int _width;
    unsigned int _height;
public:
    const Texture& bind() const;
    unsigned int LoadTexture(string const &path, TEX_TYPE type = TEX_TYPE::DEFAULT);
    unsigned int LoadCubemap(vector<string> const &faces);
    unsigned int LoadFromImap2d(imap2d const &map, int width, int height);
    // RESERVED FOR MODEL
    unsigned int LoadFromFile(string const &path, string const &directory, 
                                TEX_TYPE type, bool gamma);
};

using texture_vector = vector<Texture>;

#endif