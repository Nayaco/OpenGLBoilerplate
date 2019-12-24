# version 440 core

layout (location=0) in vec3 Position;
layout (location=1) in vec3 Normal;
layout (location=2) in vec2 TexCoord;
layout (location=3) in vec3 Tangent;
layout (location=4) in vec3 Bitangent;

layout (location=0) out vec4 Inner_Position;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    Inner_Position = vec4(Position, 1.0f);
    gl_Position = projection * view * model * vec4(Position, 1.0f);
}
