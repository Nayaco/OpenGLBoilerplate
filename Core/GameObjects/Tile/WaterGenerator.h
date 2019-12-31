//
// Created by Henry Little on 2019/12/28.
//

#ifndef SOLAR_WATERGENERATOR_H
#define SOLAR_WATERGENERATOR_H


#include "WaterTile.h"
#include "Core/Utility/ByteBuffer.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class WaterGenerator {
public:
    static WaterTile generate(int gridCount, float height);

    static ByteBuffer createMeshData(int gridCount, int totalVertexCount);

    static void storeTriangle(glm::vec2 *vertices, ByteBuffer &buffer, bool left);

    static void storeVertex(ByteBuffer &buffer, glm::vec2 v0, glm::vec2 v1, glm::vec2 v2);

    static GLuint createWaterVAO(const ByteBuffer &buffer);
private:
    const static int VERTICES_PER_SQUARE;
    const static int VERTEX_SIZE_BYTES;
};


#endif //SOLAR_WATERGENERATOR_H
