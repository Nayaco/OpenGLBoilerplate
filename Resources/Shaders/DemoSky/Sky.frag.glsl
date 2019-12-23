# version 440 core

layout (location=0) in vec3 TexCoord_inner;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform samplerCube texture_cube_0;

out vec4 FragColor;

void main() {    
    FragColor = texture(texture_cube_0, TexCoord_inner);
}