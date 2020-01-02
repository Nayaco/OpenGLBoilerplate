#include "AABBObject.hpp"

AABBObject::AABBObject(glm::vec3 _size) {
    size = _size;
    max_len = glm::length(size);
}

void AABBObject::update(glm::vec3 position) {
    this->position = position;
}

bool AABBObject::checkCollision(AABBObject const &object) {
    // if (glm::length(position - object.position) >= max_len && ) {
    //     return false;
    // }
    // else {
        bool collisionX = position.x + size.x >= object.position.x &&
            object.position.x + object.size.x >= position.x;
        bool collisionY = position.y + size.y >= object.position.y &&
            object.position.y + object.size.y >= position.y;
        bool collisionZ = position.z + size.z >= object.position.z &&
            object.position.z + object.size.z >= position.z;
        return collisionX && collisionY && collisionZ;
    // }
}

bool AABBObject::checkCollision(imap2d const& heightmap, float height) {
    int posx = position.x + size.x;
    int posz = position.z + size.z;
    if (posx >= 24 || posz >= 24 || posx <= -24 || posz <= -24)
        return false;
    return position.y <= heightmap[posx + 25][posz + 25] * height + 1.0 ||
            position.y <= heightmap[posx + 25][posz + 24] * height + 1.0 ||
            position.y <= heightmap[posx + 24][posz + 25] * height + 1.0 ||
            position.y <= heightmap[posx + 24][posz + 24] * height + 1.0;
}
