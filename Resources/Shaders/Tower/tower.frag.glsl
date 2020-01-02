# version 330 core

struct PointLight {
    vec3 pos;
    vec3 color;
};

struct ParallelLight {
    vec3 dir;
    vec3 color;
};

in vec3 TexPosition; 
in vec3 TexNormal;
in vec2 TexCoords;

out vec4 FragColor;

uniform vec3 viewpos;

uniform PointLight plight_0;
uniform PointLight plight_1;
uniform PointLight plight_2;

uniform ParallelLight alight_0;
uniform ParallelLight alight_1;
uniform ParallelLight alight_2;

uniform sampler2D texture_diffuse1;

void main() {
    vec3 lightDir = alight_0.dir;
    vec3 viewDir = normalize(viewpos - TexPosition);
    vec3 normDir = normalize(TexNormal);
    vec3 reflectDir = reflect(lightDir, normDir);

    vec3 diffuse = max(dot(normDir, lightDir), 0.0) * texture(texture_diffuse1, TexCoords).rgb;

    vec3 color_base = 0.8 * diffuse * alight_0.color + 0.2 * alight_0.color;

    FragColor = vec4(color_base, 1.0);
}