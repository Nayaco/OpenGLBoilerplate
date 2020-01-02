# version 330 core

layout (location=0) in vec3 Position;
layout (location=1) in vec3 Normal;
layout (location=2) in vec2 TexCoord;
layout (location=3) in vec3 Tangent;
layout (location=4) in vec3 Bitangent;

out VS_OUT{
    vec4 GLPosition;
    vec3 FragPosition;
} vs_out;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform float reflection_refraction;

void main() {
    vec4 pos = model * vec4(Position, 1.0f);
    vs_out.FragPosition = pos.xyz / pos.w;
    vs_out.GLPosition = gl_Position = projection * view * model * vec4(Position, 1.0f);
    if (reflection_refraction > 0.5) {
        gl_ClipDistance[0] = dot(pos, vec4(0, 1, 0,  2.5));
        gl_ClipDistance[1] = dot(pos, vec4(0, -1, 0, 2.5));
    }
}
