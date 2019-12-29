# version 440 core

out vec4 FragColor;
uniform vec3 suncolor;

void main() {
    FragColor = vec4(suncolor, 1.0);
}