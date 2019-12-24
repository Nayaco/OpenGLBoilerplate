#include "ALight.hpp"

ALight::ALight(int _lightID): lightID(_lightID) { }

void ALight::light(Shader const& shader) const {
    shader.setVec3("alight_dir_" + std::to_string(lightID), lightDir);
    if (lightOn) {
        shader.setVec3("alight_color_" + std::to_string(lightID), lightColor);
    } else {
        shader.setVec3("alight_color_" + std::to_string(lightID), glm::vec3(0.0f, 0.0f, 0.0f));
    }
}

void ALight::setUpALight(glm::vec3 _dir, glm::vec3 _color) {
    lightDir = _dir;
    lightColor = _color;
    lightOn = false;
}

void ALight::enable() { lightOn = true; }

void ALight::disable() { lightOn = false; }