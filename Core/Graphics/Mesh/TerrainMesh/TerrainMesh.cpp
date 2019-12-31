#include "TerrainMesh.hpp"

TerrainMesh::TerrainMesh(texture_vector textures, imap2d &heightmap, float _width, float _height, float _tess_level) {
    mesh_width = _width;
    mesh_height = _height;
    this->tess_level = _tess_level;
    this->textures = textures;
    
    genVertexes(heightmap);
    setupMesh(); 
}

TerrainMesh::~TerrainMesh() {}

void TerrainMesh::draw(Shader const &shader) const {
    unsigned int normalNr   = 1;
    unsigned int heightNr   = 1;
    for(size_t i = 0; i < textures.size(); i++) {
        string name;
        unsigned int number;
        glActiveTexture(GL_TEXTURE0 + i);
        switch (textures[i]._texture_type) {
            case TEX_TYPE::DEFAULT:     {name = "texture_color"; number = 0; break;}
            case TEX_TYPE::NORMALMAP:   {name = "texture_normal"; number = normalNr; normalNr++; break;}
            case TEX_TYPE::HEIGHTMAP:   {name = "texture_height"; number = heightNr; heightNr++; break;}
            default: {throw "TERMESH: texture type unusable";}              
        }
        shader.setInt(name + "_" + std::to_string(number), i);
        textures[i].bind();
    }
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBindVertexArray(VAO);
    
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    // glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBindVertexArray(0);
    glActiveTexture(GL_TEXTURE0);
}

void TerrainMesh::setupMesh() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);  
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

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

void TerrainMesh::genVertexes(imap2d &heightmap) {
    float mesh_batch_width = 1.0f / (float)mesh_width / tess_level;
    float mesh_batch_height = 1.0f / (float)mesh_height / tess_level;
    for (auto i = 0; i < tess_level * mesh_width + 1; ++i) {
        for (auto j = 0; j < tess_level * mesh_height + 1; ++j) {
            float U = mesh_batch_width * i;
            float V = mesh_batch_height * j;
            float u = mesh_batch_width * i * mesh_width;
            float v = mesh_batch_height * j * mesh_height;
            float lf = floor(u);
            float rt = ceil(u);
            float dn = floor(v);
            float up = ceil(v);
            
            if (lf > mesh_width - 1) lf -= 1.0f;
            if (rt > mesh_width - 1) rt -= 1.0f;
            if (dn > mesh_height - 1) dn -= 1.0f;
            if (up > mesh_height - 1) up -= 1.0f;
            
            float uplerp = noise::lerp(heightmap[lf][up] , heightmap[rt][up], u - lf);
            float dnlerp = noise::lerp(heightmap[lf][dn] , heightmap[rt][dn], u - lf);
            float reshi = noise::lerp(dnlerp, uplerp, v - dn);

            vertices.push_back(Vertex{position:glm::vec3(U, reshi,V)});
        }
    }
    
    bool horizontal = true, 
         vertical = true;
    for (auto i = 0; i < tess_level * mesh_width; ++i) {
        for (auto j = 0; j < tess_level * mesh_height; ++j) {
            if (horizontal ^ vertical) {
                indices.push_back(i * (tess_level * mesh_height + 1) + j);
                indices.push_back(i * (tess_level * mesh_height + 1) + j + 1);
                indices.push_back((i + 1) * (tess_level * mesh_height + 1) + j + 1);
            } else {
                indices.push_back(i * (tess_level * mesh_height + 1) + j);
                indices.push_back(i * (tess_level * mesh_height + 1) + j + 1);
                indices.push_back((i + 1) * (tess_level * mesh_height + 1) + j);
            } 
            if (horizontal ^ vertical) {
                indices.push_back(i * (tess_level * mesh_height + 1) + j);
                indices.push_back((i + 1) * (tess_level * mesh_height + 1) + j + 1);
                indices.push_back((i + 1) * (tess_level * mesh_height + 1) + j);
            } else {
                indices.push_back(i * (tess_level * mesh_height + 1) + j + 1);
                indices.push_back((i + 1) * (tess_level * mesh_height + 1) + j + 1);
                indices.push_back((i + 1) * (tess_level * mesh_height + 1) + j);
            }
            horizontal = !horizontal;
        }
        vertical = !vertical;
    }
}
