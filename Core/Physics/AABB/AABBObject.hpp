#ifndef AABBOBJECT_HPP
#define AABBOBJECT_HPP

#include "Core/Common.hpp"

class AABBObject {
    glm::vec3 position;
    glm::vec3 size;
    float max_len;
public:
    AABBObject(glm::vec3 _size);
    void update(glm::vec3 position);
    bool checkCollision(AABBObject const &object);
    bool checkCollision(imap2d const& heightmap, float height);
};
#endif