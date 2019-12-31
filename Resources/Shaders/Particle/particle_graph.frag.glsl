#version 330 core
in vec2 ColorTexCoord;

layout (location=0) out vec4 FragColor;
layout (location=1) out vec4 Brightness;

uniform float     alpha;

void main() {
    FragColor = vec4(0.8, 0.8, 0.8, alpha);
    // if(FragColor.a < 0.1) discard;
    
    // if()
}
