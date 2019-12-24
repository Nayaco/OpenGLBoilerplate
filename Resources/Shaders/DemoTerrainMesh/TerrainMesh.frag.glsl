# version 440 core
layout(location = 0) in vec4 Inner_Position;
// layout(location = 1) in vec4 Normal;
// layout(location = 2) in vec4 WorldPos;
// layout(location = 3) in vec2 UV;
// layout(location = 4) in vec4 Color;

out vec4 FragColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    FragColor = vec4(Inner_Position.y, Inner_Position.y, Inner_Position.y, 1.0f);
}