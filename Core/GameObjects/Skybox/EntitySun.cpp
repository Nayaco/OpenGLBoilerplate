#include "EntitySun.hpp"


EntitySun::EntitySun() 
    :entity_model(1.0), entity_suncolor(1.0) { 
    genSphere(vertices, indices, glm::vec3(0.0), 1.0, 64);
    setupMesh();
}

void EntitySun::draw(const Shader &shader) const {
    shader.use();
    shader.setMat4("model", entity_model);
    shader.setVec3("suncolor", entity_suncolor);
    
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    
    glBindVertexArray(0);
}

void EntitySun::update(glm::vec3 sunpos, glm::vec3 suncolor) {
    entity_sunpos = sunpos;
    entity_model = glm::translate(glm::mat4(1.0), 5.0f * sunpos);
    entity_model = glm::scale(entity_model, glm::vec3(0.1, 0.1, 0.1));
    entity_suncolor = suncolor;
}

void EntitySun::setupMesh() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);  
    
    glGenBuffers(1, &EBO);
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

void EntitySun::genSphere(vertex_vector &_vertices, indice_vector &_indices,
                glm::vec3 center, float radius, int division) {
    float step = 1.0f / (float)(division - 1);
    float u = 0.0f;
    float v = 0.0f;
    for (auto i = 0; i < division; ++i) {
        v = 0.0f;
        for (auto j = 0; j < division; ++j) {
            glm::vec3 pos = glm::vec3(radius * cos(2.0f * M_PI * u) * sin(M_PI * v),
                            radius * sin(2.0f * M_PI * u) * sin(M_PI * v),
                            radius * cos(M_PI * v)) + center; // world axis (x, y, z)
            glm::vec3 norm = normalize(pos - center); 
            _vertices.push_back(Vertex {position: pos, normal: norm, texCoords: glm::vec2(u, v)});
            v += step;
        }
        u += step;
    }
    for (auto i = 0; i < division - 1; ++i) {
        for (auto j = 0; j < division - 1; ++j) {
            unsigned int p00 = i * division + j;
			unsigned int p01 = i * division + j + 1;
			unsigned int p10 = (i + 1) * division + j;
			unsigned int p11 = (i + 1) * division + j + 1;

			_indices.push_back(p00);
			_indices.push_back(p10);
			_indices.push_back(p01);

			_indices.push_back(p01);
			_indices.push_back(p10);
			_indices.push_back(p11);
        }
    }
}