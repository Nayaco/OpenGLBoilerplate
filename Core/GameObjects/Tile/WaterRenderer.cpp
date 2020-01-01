//
// Created by Henry Little on 2019/12/28.
//

//
// Created by Henry Little on 2019/12/28.
//

#include "WaterRenderer.h"

const float WaterRenderer::WAVE_SPEED = 0.00015f;

WaterRenderer::WaterRenderer(){
    time = 0.0f;
}

void WaterRenderer::render(const Shader &shader, WaterTile *water, Camera &camera,
                           GLuint reflectionTexture, GLuint refractionTexture, GLuint depthTexture) {
//    prepare(water, camera);
    glBindVertexArray(water->vao);
    shader.use();
    shader.setFloat("height", water->height);
    time += WAVE_SPEED;
    shader.setFloat("waveTime", time);
    loadCameraVariables(shader, camera);
    // bind all the textures
    // bindTextures(reflectionTexture, refractionTexture, depthTexture);
    glDrawArrays(GL_TRIANGLES, 0, water->vertexCount);
    // reset to default
    glDisable(GL_BLEND);
    glBindVertexArray(0);
    glUseProgram(0);
}

void WaterRenderer::updateTime(const Shader &shader) {
    time += WAVE_SPEED;
    shader.setFloat("waveTime", time);
}

void WaterRenderer::loadCameraVariables(const Shader &shader, const Camera &camera) {
    shader.setMat4("projection", camera.GetProjectionMatrix());
    shader.setMat4("view", camera.GetViewMatrix());
    shader.setVec3("cameraPos", camera.GetViewPosition());
    shader.setVec2("nearFarPlanes", camera.GetNearFar());
}

void WaterRenderer::loadLightVariables(const Shader &shader) {
    shader.setVec2("lightBias", glm::vec2(0.0f, 0.0f));
    shader.setVec3("lightColour", glm::vec3(1.0f, 1.0f, 1.0f));
    shader.setVec3("lightDirection", glm::vec3(1.0f, 1.0f, 1.0f));
}


void WaterRenderer::bindTextures(const Shader &shader, GLuint reflection, GLuint refraction, GLuint depth) {
    shader.use();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, reflection);
    shader.setInt("reflectionTexture", 0);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, refraction);
    shader.setInt("refractionTexture", 1);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, depth);
    shader.setInt("depthTexture", 2);
}



