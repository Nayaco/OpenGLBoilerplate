# version 330 core

layout (location=0) out vec4 FragColor;

in vec2 ColorTexCoord;

uniform sampler2D cloud_textureA;
uniform sampler2D cloud_textureB;
uniform sampler2D cloud_textureC;
uniform sampler2D cloud_textureD;

uniform float offset_x;
uniform float offset_z;
uniform float day_and_night;

void main() {
    vec3 cloudparam;
    vec2 color_tex_origin = ColorTexCoord - vec2(0.5, 0.5) + vec2(offset_x, offset_z);
    if (color_tex_origin.x <= 0 && color_tex_origin.y <= 0) {
        cloudparam =
            texture(cloud_textureA, ColorTexCoord + vec2(0.5, 0.5) + vec2(offset_x, offset_z)).rrr;
    } 
    else if (color_tex_origin.x > 0 && color_tex_origin.y < 0) {
        cloudparam = 
            texture(cloud_textureB, ColorTexCoord + vec2(-0.5, 0.5) + vec2(offset_x, offset_z)).rrr;
    } 
    else if (color_tex_origin.x < 0 && color_tex_origin.y > 0) {
        cloudparam = 
            texture(cloud_textureC, ColorTexCoord + vec2(0.5, -0.5) + vec2(offset_x, offset_z)).rrr;
    } 
    else {
        cloudparam = 
            texture(cloud_textureD, ColorTexCoord + vec2(-0.5, -0.5) + vec2(offset_x, offset_z)).rrr;
    }
    if (cloudparam.r < 0.55) 
        FragColor = vec4(0.0, 0.0, 0.0, 1.0);
    else if(cloudparam.r < 0.6)
        FragColor = vec4(cloudparam / 1.1 * day_and_night, 1.0);
    else 
        FragColor = vec4(cloudparam * day_and_night, 1.0);
}
