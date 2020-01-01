# version 330 core

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
    vec3 color_base = 0.7 * diffuse * vec3(alight_0.color) + 0.3 * alight_0.color;
    if (fs_in.FragPosition.y > 4.0) {
        FragColor = vec4(color_base * fs_in.FragPosition.y / 5.7, 1.0);
    } else if (fs_in.FragPosition.y < 2.0){
        FragColor = vec4(color_base * vec3(0.7, 0.6, 0.3), 1.0);
    } else {
        FragColor = vec4(color_base * vec3(0.7, 1.0 * fs_in.FragPosition.y / 5.5, 0.5 * fs_in.FragPosition.y / 5.5), 1.0);
    }

}