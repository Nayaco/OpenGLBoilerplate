#version 330 core

in vec2 ColorTexCoord;

out vec4 FragColor;

uniform sampler2D scene;
uniform sampler2D bloomBlur;
uniform sampler2D clouding;

uniform bool bloom;
uniform float exposure;

void main()
{             
    const float gamma = 1.1;
    vec3 hdrColor = texture(scene, ColorTexCoord).rgb;     
    vec3 bloomColor = texture(bloomBlur, ColorTexCoord).rgb;
    if(bloom)
        hdrColor += bloomColor; // additive blending
    // tone mapping
    vec3 result = vec3(1.0) - exp(-hdrColor * exposure);
    // also gamma correct while we're at it       
    result = pow(result, vec3(1.0 / gamma));
    FragColor = vec4(result, 1.0);
}