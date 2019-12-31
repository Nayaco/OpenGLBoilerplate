#version 330 core

layout (location=0) in vec3 Position;
layout (location=1) in vec3 Normal;
layout (location=2) in vec2 TexCoord;
layout (location=3) in vec3 Tangent;
layout (location=4) in vec3 Bitangent;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    vec4 pos = projection * view * model * vec4(Position, 1.0);
    gl_Position = pos;
}