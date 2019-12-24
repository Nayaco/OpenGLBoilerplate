#ifndef ALIGHT_HPP
#define ALIGHT_HPP
#include "BaseLight.hpp"

class ALight : public BaseLight {
public:
    int lightID;
    glm::vec3 lightDir;
    glm::vec3 lightColor;
    
    bool lightOn;

    ALight(int _lightID);

    virtual void light(Shader const& shader) const override;
    virtual void setUpALight(glm::vec3 , glm::vec3 );
    virtual void enable();
    virtual void disable();
    
};

#endif