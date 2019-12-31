//
// Created by Henry Little on 2019/12/28.
//

#include "WaterRenderer.h"

const float WaterRenderer::WAVE_SPEED = 0.00015f;

WaterRenderer::WaterRenderer() :
        waterShader("water/water.v.glsl", "water/water.f.glsl") {
    time = 0.0f;
    std::cout << "Shader loaded: " << waterShader.ID << std::endl;
}

void WaterRenderer::render(const WaterTile &water, Camera &camera,
                           GLuint reflectionTexture, GLuint refractionTexture, GLuint depthTexture) {
//    prepare(water, camera);
    glEnable(GL_BLEND);
    glBindVertexArray(water.vao);
    waterShader.use();
    waterShader.setFloat("height", water.height);
    updateTime();
    loadCameraVariables(camera);
    // bind all the textures
    bindTextures(reflectionTexture, refractionTexture, depthTexture);
    glDrawArrays(GL_TRIANGLES, 0, water.vertexCount);
    // reset to default
    glDisable(GL_BLEND);
    glBindVertexArray(0);
    glUseProgram(0);
}

void WaterRenderer::updateTime() {
    time += WAVE_SPEED;
    waterShader.setFloat("waveTime", time);
}

void WaterRenderer::loadCameraVariables(const Camera &camera) {
    waterShader.setMat4("projection", camera.GetProjectionMatrix());
    waterShader.setMat4("view", camera.GetViewMatrix());
    waterShader.setVec3("cameraPos", camera.GetViewPosition());
    waterShader.setVec2("nearFarPlanes", camera.GetNearFar());
}

void WaterRenderer::loadLightVariables() {
    waterShader.setVec2("lightBias", glm::vec2(0.0f, 0.0f));
    waterShader.setVec3("lightColour", glm::vec3(1.0f, 1.0f, 1.0f));
    waterShader.setVec3("lightDirection", glm::vec3(1.0f, 1.0f, 1.0f));
}



void WaterRenderer::bindTextures(GLuint reflection, GLuint refraction, GLuint depth) {
    waterShader.use();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, reflection);
    waterShader.setInt("reflectionTexture", 0);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, refraction);
    waterShader.setInt("refractionTexture", 1);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, depth);
    waterShader.setInt("depthTexture", 2);
}



