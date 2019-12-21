#ifndef BASEMESH_HPP
#define BASEMESH_HPP

#include "Core/Common.hpp"
#include "Core/Graphics/Shader/Shader.hpp"
#include "Core/Graphics/Texture/Texture.hpp"
struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
    glm::vec3 tangent;
    glm::vec3 bitangent;
};
using vertex_vector = vector<Vertex>;
class BaseMesh {
public:
    virtual void Draw(Shader const &shader) const = 0;
private:
    virtual void setupMesh() = 0;
};
#endif