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

uniform sampler2D cloud_texture;

void main() {
    // vec2 sphereTexCoords = normalize(tmpos.xz) * cos(asin(tmpos.y)) * 0.5 + 0.5;
    float cloud_coord_height = 1.0;
    float cloud_tex_edge_len = 4.0;
    float cloud_tex_radius = 10.0;
    vec3 cloud_tex_sphere_center = vec3(0.0, -9.0, 0.0);
    vec2 cloud_tex_coord = vec2(-1.0, -1.0);

    vec3 tmpos = normalize(fs_in.ColorPosition * 2.0 - 1.0);
    if (tmpos.y > 0) {
        // float cloud_rad_offset = length(tmpos - cloud_tex_sphere_center);
        // vec3 cloud_tmp_coord = tmpos.xz
        // vec2 cloud_tex_coord_offset = 
        cloud_tex_coord = (vec2(tmpos.xz * (cloud_coord_height / tmpos.y)) / cloud_tex_edge_len);
        cloud_tex_coord = cloud_tex_coord * pow(dot(cloud_tex_coord, cloud_tex_coord), 0.8) / pow(2.0, 0.8);
        cloud_tex_coord = (cloud_tex_coord + 1.0) / 2.0;
    }

    if (fs_in.ColorType.x == 1.0) {
        FragColor = texture(texture_skymap_rt, fs_in.ColorTexCoord.zy);
        if (cloud_tex_coord.x >= 0.0 && cloud_tex_coord.y >= 0.0 && cloud_tex_coord.x <= 1.0 && cloud_tex_coord.y <= 1.0) {
            float factor = texture(cloud_texture, cloud_tex_coord).r;
            // float mixfac = exp(-length(cloud_tex_coord) * 0.2);
            FragColor = mix(FragColor, vec4(1.0), factor);
        }
    }
    else if (fs_in.ColorType.x == -1.0) {
        FragColor = texture(texture_skymap_lf, fs_in.ColorTexCoord.zy);
        if (cloud_tex_coord.x >= 0.0 && cloud_tex_coord.y >= 0.0 && cloud_tex_coord.x <= 1.0 && cloud_tex_coord.y <= 1.0) {
            float factor = texture(cloud_texture, cloud_tex_coord).r;
            // float mixfac = exp(-length(cloud_tex_coord) * 0.2);
            FragColor = mix(FragColor, vec4(1.0), factor);
        }
    }
    else if (fs_in.ColorType.y == 1.0) {
        FragColor = texture(texture_skymap_up, fs_in.ColorTexCoord.xz);
        float factor = texture(cloud_texture, cloud_tex_coord).r;
        // float mixfac = exp(-length(cloud_tex_coord) * 0.2);
        FragColor = mix(FragColor, vec4(1.0), factor);
    }
    else if (fs_in.ColorType.y == -1.0) {
        FragColor = texture(texture_skymap_dn, vec2(fs_in.ColorTexCoord.x, 1.0 - fs_in.ColorTexCoord.z));
    }
    else if (fs_in.ColorType.z == -1.0) {
        FragColor = texture(texture_skymap_ft, fs_in.ColorTexCoord.xy);
        if (cloud_tex_coord.x >= 0.0 && cloud_tex_coord.y >= 0.0 && cloud_tex_coord.x <= 1.0 && cloud_tex_coord.y <= 1.0) {
            float factor = texture(cloud_texture, cloud_tex_coord).r;
            // float mixfac = exp(-length(cloud_tex_coord) * 0.2);
            FragColor = mix(FragColor, vec4(1.0), factor);
        }
    }
    else if (fs_in.ColorType.z == 1.0) {
        FragColor = texture(texture_skymap_bk, fs_in.ColorTexCoord.xy);
        if (cloud_tex_coord.x >= 0.0 && cloud_tex_coord.y >= 0.0 && cloud_tex_coord.x <= 1.0 && cloud_tex_coord.y <= 1.0) {
            float factor = texture(cloud_texture, cloud_tex_coord).r;
            // float mixfac = exp(-length(cloud_tex_coord) * 0.2);
            FragColor = mix(FragColor, vec4(1.0), factor);
        }
    }
}
