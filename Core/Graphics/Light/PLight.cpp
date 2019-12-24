#include "PLight.hpp"

PLight::PLight(int _lightID): lightID(_lightID) { }

void PLight::light(Shader const& shader) const {
    shader.setVec3("plight_pos_" + std::to_string(lightID), lightPos);
    if (lightOn) {
        shader.setVec3("plight_color_" + std::to_string(lightID), lightColor);
    } else {
        shader.setVec3("plight_color_" + std::to_string(lightID), glm::vec3(0.0f, 0.0f, 0.0f));
    }
}

void PLight::setUpPLight(glm::vec3 _pos, glm::vec3 _color) {
    lightPos = _pos;
    lightColor = _color;
    lightOn = false;
}

void PLight::enable() { lightOn = true; }

void PLight::disable() { lightOn = false; }