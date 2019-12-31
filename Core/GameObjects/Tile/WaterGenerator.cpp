//
// Created by Henry Little on 2019/12/28.
//

#include <iostream>
#include "WaterGenerator.h"


const int WaterGenerator::VERTICES_PER_SQUARE = 3 * 2;
const int WaterGenerator::VERTEX_SIZE_BYTES = 8 + 4;

WaterTile WaterGenerator::generate(int gridCount, float height) {
    int totalVertexCount = gridCount * gridCount * VERTICES_PER_SQUARE;
    ByteBuffer meshData = createMeshData(gridCount, totalVertexCount);
    unsigned int vao = createWaterVAO(meshData);
    return WaterTile(vao, totalVertexCount, height);
}

ByteBuffer WaterGenerator::createMeshData(int gridCount, int totalVertexCount) {
    int byteSize = VERTEX_SIZE_BYTES * totalVertexCount;
    auto buffer = ByteBuffer(byteSize);
    for (int row = 0; row < gridCount; row++) {
        for (int col = 0; col < gridCount; col++) {
            // store a grid of two triangles
            auto vertices = new glm::vec2[4];
            vertices[0] = glm::vec2(col, row);
            vertices[1] = glm::vec2(col, row + 1);
            vertices[2] = glm::vec2(col + 1, row);
            vertices[3] = glm::vec2(col + 1, row + 1);
            storeTriangle(vertices, buffer, true);
            storeTriangle(vertices, buffer, false);
        }
    }
    return buffer;
}

void WaterGenerator::storeTriangle(glm::vec2 *vertices, ByteBuffer &buffer, bool left) {
    // 0------2
    // |   /  |
    // | /    |
    // 1------3
    // 0 1 2 and 2 1 3
    int idx0 = left ? 0 : 2;
    int idx1 = 1;
    int idx2 = left ? 2 : 3;
    storeVertex(buffer, vertices[idx0], vertices[idx1], vertices[idx2]);
    storeVertex(buffer, vertices[idx1], vertices[idx2], vertices[idx0]);
    storeVertex(buffer, vertices[idx2], vertices[idx0], vertices[idx1]);
}

void WaterGenerator::storeVertex(ByteBuffer &buffer, glm::vec2 v0, glm::vec2 v1, glm::vec2 v2) {
    buffer.write(&(v0.x), sizeof(float));
    buffer.write(&(v0.y), sizeof(float));
    char * indicators = new char[4];
    indicators[0] = (char)(v1.x - v0.x);
    indicators[1] = (char)(v1.y - v0.y);
    indicators[2] = (char)(v2.x - v0.x);
    indicators[3] = (char)(v2.y - v0.y);
    buffer.write(indicators, sizeof(int));
}


GLuint WaterGenerator::createWaterVAO(const ByteBuffer &buffer) {
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    // bind the vbo
    GLuint posVbo;
    glGenBuffers(1, &posVbo);
    glBindBuffer(GL_ARRAY_BUFFER, posVbo);
//    glBufferData(GL_ARRAY_BUFFER, buffer.length(), buffer.getByteArray(), GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, buffer.length(), buffer.getByteArray(), GL_STATIC_DRAW);
    // attribute 0
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, VERTEX_SIZE_BYTES, nullptr);
    // attribute 1
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_BYTE, GL_FALSE, VERTEX_SIZE_BYTES, (void*)(uintptr_t)8);
    // unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    return vao;
}

