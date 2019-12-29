#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include "Core/Common.hpp"
#include "Core/Utility/Random.hpp"
enum class TEX_TYPE: unsigned int {
    DEFAULT    = 0,
    CUBEMAP    = 1,

    DIFFUSEMAP = 10,
    SPECULARMAP= 11,
    NORMALMAP  = 12,
    HEIGHTMAP  = 13,
    AMBIENTMAP = 14,

    COLORBUF   = 20,
};

struct Texture {
    unsigned int _id;
    std::string  _path;
    unsigned int _type;
    unsigned int _format;
    unsigned int _width;
    unsigned int _height;
    unsigned int _warpr;
    unsigned int _warps;
    unsigned int _warpt;
    unsigned int _filter_min;
    unsigned int _filter_max;
    TEX_TYPE     _texture_type;
    Texture();
    void destroy();
    const Texture& bind() const;

    void GenRandomMap1D(
        unsigned int size);

    void LoadTexture2D(
        unsigned int width, unsigned int height, const unsigned char *data);
    
    void LoadTexture2DGamma(
        unsigned int width, unsigned int height, const unsigned char *data);

    void LoadTexture2DFloat(
        unsigned int width, unsigned int height, const float *data);

    void LoadTexture3D(
        unsigned int width, unsigned int height, unsigned char **data);

    void GenShadowMap(unsigned int width, unsigned int height);

    void GenPostProcessMap(unsigned int width, unsigned int height);
};

using texture_vector = vector<Texture>;

#endif