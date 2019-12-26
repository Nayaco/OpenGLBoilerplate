#version 440

layout (location=0) in vec3 Position;
layout (location=1) in vec3 Normal;
layout (location=2) in vec2 TexCoord;
layout (location=3) in vec3 Tangent;
layout (location=4) in vec3 Bitangent;

layout (location=0) out vec3 ColorPosition;
layout (location=1) out vec3 ColorTexCoord;
layout (location=2) out vec3 ColorType;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    vec4 pos      = 
        projection * view * vec4(Position.x, Position.y - 0.1, Position.z, 1.0);
    ColorPosition = Position * 0.5 + 0.5;
    ColorTexCoord = ColorPosition;
    ColorType     = Normal;
    gl_Position   = pos.xyww;
}