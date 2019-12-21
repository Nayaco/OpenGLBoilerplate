#ifndef TEXTURE_HPP
#define TEXTURE_HPP

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
public:
    const Texture& bind() const;
    unsigned int LoadTexture(string const &path);
    unsigned int LoadCubemap(vector<string> const &faces);
    unsigned int LoadFromFile(string const &path, string const &directory, 
                                TEX_TYPE type, bool gamma);
};

using texture_vector = vector<Texture>;

#endif