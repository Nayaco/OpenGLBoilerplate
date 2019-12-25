# version 440 core

in GS_OUT{
    vec3 FragPosition;
    vec3 FragNormal;
} fs_in;

struct PointLight {
    vec3 pos;
    vec3 color;
};

struct ParallelLight {
    vec3 dir;
    vec3 color;
};

out vec4 FragColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 viewpos;

uniform PointLight plight_0;
uniform PointLight plight_1;
uniform PointLight plight_2;

uniform ParallelLight alight_0;
uniform ParallelLight alight_1;
uniform ParallelLight alight_2;

void main() {
    vec3 lightDir = alight_0.dir;
    vec3 viewDir = normalize(viewpos - fs_in.FragPosition);
    vec3 normDir = normalize(fs_in.FragNormal);
    vec3 reflectDir = reflect(lightDir, normDir);
    
    float diffuse = max(dot(normDir, lightDir), 0.0);
    FragColor = vec4(diffuse * vec3(alight_0.color), 1.0);
}