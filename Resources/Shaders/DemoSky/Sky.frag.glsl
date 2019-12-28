# version 440 core

in vec3 TexCoord_inner;

out vec4 FragColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform samplerCube texture_cube_0;


void main() {    
    FragColor = texture(texture_cube_0, TexCoord_inner);
}