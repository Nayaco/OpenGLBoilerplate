#ifndef BASESCENE_HPP
#define BASESCENE_HPP

#include "Core/Common.hpp"

class BaseScene {
public:
    virtual void draw() const = 0;
    virtual void initialize() = 0;
    virtual void destory() = 0;
    virtual void update() = 0;

};

using scene_vector = vector<BaseScene*>;
#endif