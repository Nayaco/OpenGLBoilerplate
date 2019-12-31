#version 440 core
in vec2 ColorTexCoord;

out vec4 FragColor;

uniform sampler2D scene;
void main()
{             
    FragColor = vec4(texture(scene, ColorTexCoord).rgb, 1.0);
}