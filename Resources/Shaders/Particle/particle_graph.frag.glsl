#version 330 core
in vec2 ColorTexCoord;

layout (location=0) out vec4 FragColor;
layout (location=1) out vec4 Brightness;

uniform float     alpha;
uniform vec3      color;     
void main() {
    FragColor = vec4(color, alpha);
    Brightness = vec4(0.0);
    if(FragColor.r > 1.0) Brightness = FragColor;
    
}
