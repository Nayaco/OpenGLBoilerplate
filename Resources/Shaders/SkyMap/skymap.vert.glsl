# version 440 core

layout (location=0) in vec3 Position;
layout (location=1) in vec3 Normal;
layout (location=2) in vec2 TexCoord;
layout (location=3) in vec3 Tangent;
layout (location=4) in vec3 Bitangent;

// layout (location=0) out vec3 PositionRight;
// layout (location=1) out vec3 PositionLeft;
// layout (location=2) out vec3 PositionUp;
// layout (location=3) out vec3 PositionBottom;
// layout (location=4) out vec3 PositionFront;
// layout (location=5) out vec3 PositionBack;

out VS_OUT {
    vec3 PositionRight;
    vec3 PositionLeft;
    vec3 PositionUp;
    vec3 PositionBottom;
    vec3 PositionFront;
    vec3 PositionBack;
} vs_out;

void main() {
    gl_Position     = vec4(Position, 1.0);

    vs_out.PositionRight   = vec3(-Position.z,  Position.y,  Position.x);
    vs_out.PositionLeft    = vec3( Position.z,  Position.y,  Position.x);

    vs_out.PositionUp      = vec3( Position.x, -Position.z,  Position.y);
    vs_out.PositionBottom  = vec3( Position.x,  Position.z, -Position.y);
    
    vs_out.PositionFront   = vec3( Position.x,  Position.y,  Position.z);
    vs_out.PositionBack    = vec3( Position.x,  Position.y, -Position.z);
}