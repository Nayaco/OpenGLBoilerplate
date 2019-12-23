#include "Texture.hpp"
#include "Core/ExceptionHandle/ErrLog.hpp"
const Texture& Texture::bind() const {
    if (_type == TEX_TYPE::CUBEMAP) glBindTexture(GL_TEXTURE_CUBE_MAP, _id);
    else glBindTexture(GL_TEXTURE_2D, _id);
    return *this;
}

unsigned int Texture::LoadTexture(string const &path, TEX_TYPE type) {
    int width, height, nrChannels;
    unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
    if (data) {
        GLenum format;
        switch (nrChannels) {
            case 1: {format = GL_RED; break;}
            case 3: {format = GL_RGB; break;}
            case 4: {format = GL_RGBA; break;}
            default: throw "TEXTURE: unknow color space";
        }
        glGenTextures(1, &_id);
        glBindTexture(GL_TEXTURE_2D, _id);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        stbi_image_free(data);
    }
    else {
        stbi_image_free(data);
        throw "TEXTURE: file not exists";
    }

    _width = width;
    _height = height;
    _type = type;
    _path = path;
    _isGamma = false;
    return _id;
}

unsigned int Texture::LoadCubemap(vector<string> const &faces) {
    int width, height, nrChannels, _ext;
    glGenTextures(1, &_id);
    glBindTexture(GL_TEXTURE_CUBE_MAP, _id);
    for (size_t i = 0; i < faces.size(); ++i) {
        unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
        if (data) {
            GLenum format;
            switch (nrChannels) {
                case 1: {format = GL_RED; break;}
                case 3: {format = GL_RGB; break;}
                case 4: {format = GL_RGBA; break;}
                default: throw "TEXTURE: unknow color space";
            }
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, format, 
                            width, height, 0, format, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }
        else {
            stbi_image_free(data);
            throw "TEXTURE: file "+ std::to_string(i) + " not exists";
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    _ext = faces[0].find('.', 0);
    _path = faces[0].substr(0, _ext);
    _type = TEX_TYPE::CUBEMAP;
    _isGamma = false;
    _width = width;
    _height = height;
    return _id;
}
unsigned int Texture::LoadFromImap2d(imap2d const &map, int width, int height) {
    unsigned char *data = new unsigned char[width * height];
    for (auto i = 0; i < width; ++i) {
        for(auto j = 0; j < height; ++j) {
            data[i * height + j] = round(map[i][j] * 255);
        }
    }
    glGenTextures(1, &_id);
    glBindTexture(GL_TEXTURE_2D, _id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    stbi_image_free(data);
    
    _path = "dynamic";
    _type = TEX_TYPE::HEIGHTMAP;
    _isGamma = false;
    _width = width;
    _height = height;
    return _id;
}
unsigned int Texture::LoadFromFile(string const &path, string const &directory, 
                                    TEX_TYPE type, bool gamma) {
    int width, height, nrChannels;
    string filename = directory + "/" + path;
    unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrChannels, 0);
    if (data) {
        GLenum format;
        switch (nrChannels) {
            case 1: {format = GL_RED; break;}
            case 3: {format = GL_RGB; break;}
            case 4: {format = GL_RGBA; break;}
            default: throw "TEXTURE: unknow color space";
        }
        glGenTextures(1, &_id);
        glBindTexture(GL_TEXTURE_2D, _id);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        stbi_image_free(data);
    }
    else {
        stbi_image_free(data);
        throw "TEXTURE: file "+ filename + " not exists";
    }
    _width = width;
    _height = height;
    _path = filename;
    _type = type;
    _isGamma = gamma;
    return _id;
}