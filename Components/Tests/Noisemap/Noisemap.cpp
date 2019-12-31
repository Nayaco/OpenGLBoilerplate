#include "Noisemap.hpp"

static void ppmWrite(const char* filename, unsigned char* data, int w, int h) {
    FILE* fp;
    fp = fopen(filename, "wb");
    fprintf(fp, "P5\n%d %d\n255\n", w, h);
    fwrite(data, w * h, 1, fp);
    fclose(fp);
}

NPMT::NPMT()
    :vertices {
        Vertex {position:glm::vec3(-1.0f,  1.0, 0.0), normal:glm::vec3(0.0), texCoords:glm::vec2(0.0, 1.0)},
        Vertex {position:glm::vec3(-1.0f, -1.0, 0.0), normal:glm::vec3(0.0), texCoords:glm::vec2(0.0, 0.0)},
        Vertex {position:glm::vec3( 1.0f,  1.0, 0.0), normal:glm::vec3(0.0), texCoords:glm::vec2(1.0, 1.0)},
        Vertex {position:glm::vec3( 1.0f, -1.0, 0.0), normal:glm::vec3(0.0), texCoords:glm::vec2(1.0, 0.0)},
    } {
    mesh_width = 200;
    mesh_height = 200;
    setupMesh();
}

void NPMT::init() {
    auto npmt1 = noise::whiteNoise(mesh_width, mesh_height);
    npmt = noise::perlNoise(npmt1, 8, mesh_width, mesh_height);
    unsigned char data[mesh_width * mesh_height * 3];
    unsigned char data0[mesh_width * mesh_height];
    
    for (auto i = 0 ; i < mesh_width; ++i) {
        for (auto j = 0; j < mesh_height; ++j) {
            data0[i * mesh_height + j] = 
            data[i * mesh_height * 3 + j * 3] = 
            data[i * mesh_height * 3 + j * 3 + 1] = 
            data[i * mesh_height * 3 + j * 3 + 2] = (unsigned char)(npmt[i][j] * (float)255);
        }
    }
    tex.LoadTexture2D(mesh_width, mesh_height, data);
    ppmWrite("test.ppm", data0, mesh_width, mesh_height);
}
void NPMT::draw(Shader const& shader) const {
    shader.use();
    glActiveTexture(GL_TEXTURE0);
    tex.bind();
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
}
void NPMT::setupMesh() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);  
    
    glEnableVertexAttribArray(0);	
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(1);	
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tangent));
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, bitangent));
    
    glBindVertexArray(0);
}