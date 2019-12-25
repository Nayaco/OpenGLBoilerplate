#ifndef PLIGHT_HPP
#define PLIGHT_HPP
#include "BaseLight.hpp"

class PLight : public BaseLight {
public:
    int lightID;
    glm::vec3 lightPos;
    glm::vec3 lightColor;
    
    bool lightOn;

    PLight(int _lightID);

    virtual void use(Shader const& shader) const override;
    virtual void setUpPLight(glm::vec3 , glm::vec3 );
    virtual void enable() override;
    virtual void disable() override;
    
};

#endif