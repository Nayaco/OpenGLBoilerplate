#version 440 core
in vec2 ColorTexCoord;
out vec4 FragColor;

uniform float     alpha;

void main() {
    FragColor = vec4(0.8, 0.8, 0.8, alpha);
    if(FragColor.a < 0.1) discard;
}
