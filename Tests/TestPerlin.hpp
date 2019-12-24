#ifndef TEST_PERLIN_HPP
#define TEST_PERLIN_HPP
#include "Core/Common.hpp"
#include "Core/Utility/Noise/Noise.hpp"
#include "Core/Utility/Random.hpp"

static void ppmRead(char* filename, unsigned char* data, int* w, int* h) {
    char header[1024];
    FILE* fp = NULL;
    int line = 0;

    fp = fopen(filename, "rb");
    while (line < 2) {
        fgets(header, 1024, fp);
        if (header[0] != '#') {
            ++line;
        }
    }
    sscanf(header, "%d %d\n", w, h);
    fgets(header, 20, fp);
    fread(data, (*w) * (*h), 1, fp);

    fclose(fp);
}

static void ppmWrite(const char* filename, unsigned char* data, int w, int h) {
    FILE* fp;
    fp = fopen(filename, "wb");
    fprintf(fp, "P5\n%d %d\n255\n", w, h);
    fwrite(data, w * h, 1, fp);
    fclose(fp);
}
using std::cout;
void perl_image() {
    size_t _size = 50;
    unsigned char buff[_size * _size];
    imap2d white_map = noise::whiteNoise(_size, _size);
    for (auto i = 0; i < _size; ++i) 
        for(auto j = 0; j < _size; ++j) buff[i * _size + j] = round(white_map[i][j] * 255);
    ppmWrite("Resources/white.ppm", buff, _size, _size);
    imap2d perl_map = noise::perlNoise(white_map, 12, _size, _size);
    for (auto i = 0; i < _size; ++i) 
        for(auto j = 0; j < _size; ++j) buff[i * _size + j] = round(perl_map[i][j] * 255);
    ppmWrite("Resources/perl.ppm", buff, _size, _size);    
}

#endif