#version 330 core
struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

in vec3 normal;
in vec3 fragPos;

out vec4 FragColor;

void main()
{
    FragColor = vec4(1.0);
}