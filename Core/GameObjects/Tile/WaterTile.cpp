//
// Created by Henry Little on 2019/12/28.
//

#include "WaterTile.h"

#include <iostream>

WaterTile::WaterTile(unsigned int vao, unsigned int vertexCount, float height) :
        vao(vao), vertexCount(vertexCount), height(height) {
    std::cout << "Water tile VAO: " << vao << " with vertexCount: " << vertexCount << std::endl;
}

void WaterTile::release() {
    glDeleteVertexArrays(1, &vao);
}