#version 330 core
in vec2 TexCoords;
out vec4 color;
out vec4 Brightness;

uniform sampler2D text;
uniform vec3 textColor;

void main()
{    
    Brightness = vec4(0.0);
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, TexCoords).r);
    color = vec4(textColor, 1.0) * sampled;
    if (color.r > 1.8 && color.a > 0.5) Brightness = vec4(1.0);
}