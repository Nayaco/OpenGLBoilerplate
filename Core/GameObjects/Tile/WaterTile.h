//
// Created by Henry Little on 2019/12/28.
//

#ifndef SOLAR_WATERTILE_H
#define SOLAR_WATERTILE_H

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


#endif //SOLAR_WATERTILE_H
