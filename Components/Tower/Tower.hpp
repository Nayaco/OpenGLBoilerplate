#ifndef TOWER_HPP
#define TOWER_HPP

#include "Core/Common.hpp"
#include "Core/Graphics/Model/Model.hpp"
#include "Core/Physics/AABB/AABBObject.hpp"


struct Tower {
    glm::vec3 position;
    glm::vec3 center;
    
    AABBObject aabbbox;
    Model model;
    Tower();
    
    void draw(Shader const &shader); 
};

#endif