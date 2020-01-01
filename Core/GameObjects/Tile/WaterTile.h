#ifndef WATERTILE_H
#define WATERTILE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class WaterTile {
public:
    unsigned int vao;
    unsigned int vertexCount;
    float height;

    WaterTile(unsigned int vao, unsigned int vertexCount, float height);

    void release();
};

#endif
