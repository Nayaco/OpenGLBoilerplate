# version 440 core

layout (location=0) in vec3 Position;
layout (location=1) in vec3 Normal;
layout (location=2) in vec2 TexCoord;
layout (location=3) in vec3 Tangent;
layout (location=4) in vec3 Bitangent;

out vec3 TexCoord_inner;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    TexCoord_inner = Position;
    vec4 _pos = projection * view * vec4(Position, 1.0);
    gl_Position = _pos.xyww;
}
