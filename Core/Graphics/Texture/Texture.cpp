#include "Texture.hpp"

Texture::Texture() 
:_type(GL_RGB)
,_format(GL_RGB)
,_warpr(GL_CLAMP_TO_EDGE)
,_warps(GL_REPEAT)
,_warpt(GL_REPEAT)
,_filter_min(GL_LINEAR_MIPMAP_LINEAR)
,_filter_max(GL_LINEAR_MIPMAP_LINEAR)
,_texture_type(TEX_TYPE::DEFAULT) { }

void Texture::destroy() {
    glDeleteTextures(1, &_id);
}

const Texture& Texture::bind() const {
    if(_texture_type == TEX_TYPE::CUBEMAP) {
        glBindTexture(GL_TEXTURE_CUBE_MAP, _id);
        return *this;
    }
    glBindTexture(GL_TEXTURE_2D, _id);
    return *this;
}

void Texture::GenRandomMap1D(unsigned int size) {
    this->_width = size;
    this->_format =  GL_RGB;
    this->_type   =  GL_RGB;
    this->_filter_max = this->_filter_min = GL_LINEAR;
    this->_texture_type = TEX_TYPE::DEFAULT;
    this->_warps = GL_REPEAT;

    const imap1d data = randomx::rand(size * 3);
    
    glGenTextures(1, &_id);
    glBindTexture(GL_TEXTURE_1D, _id);
    glTexImage1D(GL_TEXTURE_1D, 0, GL_RGB, size, 0.0f, GL_RGB, GL_FLOAT, data.data());
    glTexParameterf(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_REPEAT);
}

void Texture::LoadTexture2D(unsigned int width, unsigned int height, const unsigned char *data) {
    this->_width = width; this->_height = height;
    glGenTextures(1, &_id);
    glBindTexture(GL_TEXTURE_2D, _id);
    glTexImage2D(GL_TEXTURE_2D, 0, _type, this->_width, this->_height, 0, _format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->_warps);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->_warpt);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->_filter_min);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->_filter_max);
}

void Texture::LoadTexture2DGamma(unsigned int width, unsigned int height, const unsigned char *data) {
    this->_width = width; this->_height = height;
    if (_format == GL_RGB) {
        this->_type = GL_SRGB;
    } else if (_format == GL_RGBA) {
        this->_type = GL_SRGB_ALPHA;
    }
    glGenTextures(1, &_id);
    glBindTexture(GL_TEXTURE_2D, _id);
    glTexImage2D(GL_TEXTURE_2D, 0, _type, this->_width, this->_height, 0, _format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->_warps);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->_warpt);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->_filter_min);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->_filter_max);
}

void Texture::LoadTexture2DFloat(unsigned int width, unsigned int height, const float *data) {
    this->_width = width; this->_height = height;
    glGenTextures(1, &_id);
    glBindTexture(GL_TEXTURE_2D, _id);
    glTexImage2D(GL_TEXTURE_2D, 0, this->_type, this->_width, this->_height, 0, this->_format, GL_FLOAT, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->_warps);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->_warpt);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->_filter_min);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->_filter_max);
}

void Texture::LoadTexture3D(unsigned int width, unsigned int height, unsigned char **data) {
    this->_width = width; this->_height = height;
    glGenTextures(1, &_id);
    glBindTexture(GL_TEXTURE_CUBE_MAP, _id);
    for(auto i = 0; i < 6; ++i) {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, this->_type, 
            this->_width, this->_height, 0, this->_format, GL_UNSIGNED_BYTE, data[i]);
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, this->_filter_min);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, this->_filter_max);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, this->_warpr);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, this->_warps);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, this->_warpt);
}

void Texture::GenShadowMap(unsigned int width, unsigned int height) {
    
}

void Texture::GenPostProcessMap(unsigned int width, unsigned int height) {
    this->_width = width; this->_height = height;
    this->_format =  GL_RGB;
    this->_type   =  GL_RGB;
    this->_filter_max = this->_filter_min = GL_LINEAR;
    this->_texture_type = TEX_TYPE::COLORBUF;
    this->_warpr = this->_warps = this->_warpt = GL_CLAMP_TO_EDGE;
    
    glGenTextures(1, &_id);
    glBindTexture(GL_TEXTURE_2D, _id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, this->_width, this->_height, 0, GL_RGB, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}