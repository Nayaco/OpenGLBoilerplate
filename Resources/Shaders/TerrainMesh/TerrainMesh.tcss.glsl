# version 440 core
#define id gl_InvocationID
layout(vertices = 4) out;

uniform float tess_level = 20.0f;

void main() {
    gl_out[id].gl_Position = gl_in[id].gl_Position;
    if(id == 0){
        gl_TessLevelInner[0] = tess_level;
        gl_TessLevelInner[1] = tess_level;
        gl_TessLevelOuter[0] = tess_level;
        gl_TessLevelOuter[1] = tess_level;
        gl_TessLevelOuter[2] = tess_level;
        gl_TessLevelOuter[3] = tess_level;
    }
}