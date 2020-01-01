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

    void render(const Shader &shader, WaterTile *water, Camera &camera,
                GLuint reflectionTexture, GLuint refractionTexture, GLuint depthTexture);

    void updateTime(const Shader &shader);
    
private:

    const static float WAVE_SPEED;
    float time;


    void loadCameraVariables(const Shader &shader, const Camera &camera);

    void bindTextures(const Shader &shader, GLuint reflection, GLuint refraction, GLuint depth);

    void loadLightVariables(const Shader &shader);
};


#endif //SOLAR_WATERRENDERER_H