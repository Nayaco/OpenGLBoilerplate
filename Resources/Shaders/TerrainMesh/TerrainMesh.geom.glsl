#version 330 core

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

in VS_OUT{
    vec4 GLPosition;
    vec3 FragPosition;
    // float gl_ClipDistance[2];
} gs_in[];

out GS_OUT{
    vec3 FragPosition;
    vec3 FragNormal;
    // float gl_ClipDistance[2];
} gs_out;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    vec3 vecA = vec3(gs_in[0].FragPosition) - vec3(gs_in[1].FragPosition);
    vec3 vecB = vec3(gs_in[0].FragPosition) - vec3(gs_in[2].FragPosition);    
    vec3 fragNormal = normalize(cross(vecA, vecB));

    gl_Position = gs_in[0].GLPosition;
    gs_out.FragPosition = gs_in[0].FragPosition;
    gs_out.FragNormal =   fragNormal;
    // gs_out.gl_ClipDistance[0] = gs_in[0].gl_ClipDistance[0];
    // gs_out.gl_ClipDistance[1] = gs_in[0].gl_ClipDistance[1];
    EmitVertex();
    
    gl_Position = gs_in[1].GLPosition;
    gs_out.FragPosition = gs_in[1].FragPosition;
    gs_out.FragNormal =   fragNormal;
    // gs_out.gl_ClipDistance[0] = gs_in[1].gl_ClipDistance[0];
    // gs_out.gl_ClipDistance[1] = gs_in[1].gl_ClipDistance[1];
    EmitVertex();

    gl_Position = gs_in[2].GLPosition;
    gs_out.FragPosition = gs_in[2].FragPosition;
    gs_out.FragNormal =   fragNormal;
    // gs_out.gl_ClipDistance[0] = gs_in[2].gl_ClipDistance[0];
    // gs_out.gl_ClipDistance[1] = gs_in[2].gl_ClipDistance[1];
    EmitVertex();

    EndPrimitive();
}