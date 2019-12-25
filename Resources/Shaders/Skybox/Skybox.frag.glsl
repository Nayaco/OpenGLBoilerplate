#version 440 core

layout (location=0) in vec3 ColorPosition;
layout (location=1) in vec3 ColorTexCoord;
layout (location=2) in vec3 ColorType;

out vec4 FragColor;

uniform sampler2D texture_skymap_rt;
uniform sampler2D texture_skymap_lf;
uniform sampler2D texture_skymap_up;
uniform sampler2D texture_skymap_dn;
uniform sampler2D texture_skymap_ft;
uniform sampler2D texture_skymap_bk;

void main() {
    // if (ColorType.x == 1.0) {
    //     FragColor = texture(texture_skymap_rt, vec2(1.0 - ColorTexCoord.z, ColorTexCoord.y));
    // }
    // else if (ColorType.x == -1.0) {
    //     FragColor = texture(texture_skymap_lf, ColorTexCoord.zy);
    // }
    // else if (ColorType.y == 1.0) {
    //     FragColor = texture(texture_skymap_up, vec2(ColorTexCoord.x, 1.0 - ColorTexCoord.z));
    // }
    // else if (ColorType.y == -1.0) {
    //     FragColor = texture(texture_skymap_dn, ColorTexCoord.xz);
    // }
    // else if (ColorType.z == 1.0) {
    //     FragColor = texture(texture_skymap_ft, ColorTexCoord.xy);
    // }
    // else if (ColorType.z == -1.0) {
    //     FragColor = texture(texture_skymap_bk, vec2(1.0 - ColorTexCoord.x, ColorTexCoord.y));
    // }
    if (ColorType.x == 1.0) {
        FragColor = texture(texture_skymap_rt, ColorTexCoord.zy);
    }
    else if (ColorType.x == -1.0) {
        FragColor = texture(texture_skymap_lf, ColorTexCoord.zy);
    }
    else if (ColorType.y == 1.0) {
        FragColor = texture(texture_skymap_up, ColorTexCoord.xz);
    }
    else if (ColorType.y == -1.0) {
        FragColor = texture(texture_skymap_dn, vec2(ColorTexCoord.x, 1.0 - ColorTexCoord.z));
    }
    else if (ColorType.z == -1.0) {
        FragColor = texture(texture_skymap_ft, ColorTexCoord.xy);
    }
    else if (ColorType.z == 1.0) {
        FragColor = texture(texture_skymap_bk, ColorTexCoord.xy);
    }
}
