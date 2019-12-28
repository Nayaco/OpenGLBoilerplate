#version 440 core

// layout (location=0) in vec3 ColorPosition;
// layout (location=1) in vec3 ColorTexCoord;
// layout (location=2) in vec3 ColorType;

in VS_OUT {
    vec3 ColorPosition;
    vec3 ColorTexCoord;
    vec3 ColorType;
} fs_in;

out vec4 FragColor;

uniform sampler2D texture_skymap_rt;
uniform sampler2D texture_skymap_lf;
uniform sampler2D texture_skymap_up;
uniform sampler2D texture_skymap_dn;
uniform sampler2D texture_skymap_ft;
uniform sampler2D texture_skymap_bk;

void main() {
    if (fs_in.ColorType.x == 1.0) {
        FragColor = texture(texture_skymap_rt, fs_in.ColorTexCoord.zy);
    }
    else if (fs_in.ColorType.x == -1.0) {
        FragColor = texture(texture_skymap_lf, fs_in.ColorTexCoord.zy);
    }
    else if (fs_in.ColorType.y == 1.0) {
        FragColor = texture(texture_skymap_up, fs_in.ColorTexCoord.xz);
    }
    else if (fs_in.ColorType.y == -1.0) {
        FragColor = texture(texture_skymap_dn, vec2(fs_in.ColorTexCoord.x, 1.0 - fs_in.ColorTexCoord.z));
    }
    else if (fs_in.ColorType.z == -1.0) {
        FragColor = texture(texture_skymap_ft, fs_in.ColorTexCoord.xy);
    }
    else if (fs_in.ColorType.z == 1.0) {
        FragColor = texture(texture_skymap_bk, fs_in.ColorTexCoord.xy);
    }
}
