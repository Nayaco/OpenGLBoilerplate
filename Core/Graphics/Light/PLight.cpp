#include "PLight.hpp"

PLight::PLight(int _lightID): lightID(_lightID) { }

void PLight::use(Shader const& shader) const {
    shader.setVec3("plight_" + std::to_string(lightID) + ".pos", lightPos);
    if (lightOn) {
        shader.setVec3("plight_" + std::to_string(lightID) + ".color", lightColor);
    } else {
        shader.setVec3("plight_" + std::to_string(lightID) + ".color", glm::vec3(0.0f, 0.0f, 0.0f));
    }
}

void PLight::setUpPLight(glm::vec3 _pos, glm::vec3 _color) {
    lightPos = _pos;
    lightColor = _color;
    lightOn = false;
}

void PLight::enable() { lightOn = true; }

void PLight::disable() { lightOn = false; }