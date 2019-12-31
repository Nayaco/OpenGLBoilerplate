#version 330 core

layout (location=0) in vec3 Position;
layout (location=1) in vec3 Normal;
layout (location=2) in vec2 TexCoord;
layout (location=3) in vec3 Tangent;
layout (location=4) in vec3 Bitangent;

out vec2 ColorTexCoord;

uniform mat4 projection = mat4(1.0);
uniform mat4 view;

void main()
{
    ColorTexCoord = TexCoord;
    // vec4 pos = projection * view * vec4(Position, 1.0);
    gl_Position = vec4(Position, 1.0);
}