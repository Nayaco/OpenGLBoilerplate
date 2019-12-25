#ifndef CHUNK_HPP
#define CHUNK_HPP

#include "Core/Common.hpp"
#include "Core/GameObjects/Terrain/Terrain.hpp"

class Chunk {
public:
    Terrain *terrain;
    
    float landHeight;
    float seaLevel;

    float grassDensity;
    
};

#endif