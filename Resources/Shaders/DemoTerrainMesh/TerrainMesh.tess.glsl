# version 440 core
layout(quads, equal_spacing, ccw) in;

layout(location = 0) out vec4 Position;
layout(location = 1) out vec4 Normal;
layout(location = 2) out vec4 WorldPos;
layout(location = 3) out vec2 UV;
layout(location = 4) out vec4 Color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform float heightfix_level;
uniform float scale_level;

uniform sampler2D texture_height_1;
uniform sampler2D texture_normal_1;
uniform sampler2D texture_color_1;

void main() {
    float u = gl_TessCoord.x;
    float v = gl_TessCoord.y;
    vec4 a = mix(gl_in[0].gl_Position, gl_in[1].gl_Position, u);
    vec4 b = mix(gl_in[3].gl_Position, gl_in[2].gl_Position, u);
    
    UV = gl_TessCoord.xy;
    WorldPos = mix(a, b, v);
    Normal = vec4(0.0f, 0.0f, 1.0f, 0.0f);
    
    float hi_level = texture(texture_height_1, UV).r;
    float height = hi_level * scale_level + heightfix_level;
    
    Position = gl_Position = projection * view * vec4(WorldPos.x , height / 2.0f, WorldPos.z, 1.0f);
    Color = vec4(hi_level, hi_level, hi_level, 1.0f);
}