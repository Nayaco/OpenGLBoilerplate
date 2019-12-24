#include "Texture.hpp"

Texture::Texture() 
:_type(GL_RGB)
,_format(GL_RGB)
,_warpr(GL_CLAMP_TO_EDGE)
,_warps(GL_REPEAT)
,_warpt(GL_REPEAT)
,_filter_min(GL_LINEAR_MIPMAP_LINEAR)
,_filter_max(GL_LINEAR_MIPMAP_LINEAR) { }

const Texture& Texture::bind() const {
    glBindTexture(GL_TEXTURE_2D, _id);
    return *this;
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