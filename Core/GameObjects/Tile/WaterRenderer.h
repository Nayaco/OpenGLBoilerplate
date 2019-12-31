//
// Created by Henry Little on 2019/12/28.
//

#ifndef SOLAR_WATERRENDERER_H
#define SOLAR_WATERRENDERER_H


#include "Core/Graphics/Shader/Shader.hpp"
#include "WaterTile.h"
#include "Core/GameObjects/Camera/Camera.hpp"

class WaterRenderer {
public:
    WaterRenderer();
    
    void render(const WaterTile &water, Camera &camera,
                GLuint reflectionTexture, GLuint refractionTexture, GLuint depthTexture);
private:
    
    const static float WAVE_SPEED;
    Shader waterShader;
    float time;

    void updateTime();

    void loadCameraVariables(const Camera &camera);
    void bindTextures(GLuint reflection, GLuint refraction, GLuint depth);
    void loadLightVariables();
};


#endif //SOLAR_WATERRENDERER_H
