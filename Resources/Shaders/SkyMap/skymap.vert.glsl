# version 440 core

layout (location=0) in vec3 Position;
layout (location=1) in vec3 Normal;
layout (location=2) in vec2 TexCoord;
layout (location=3) in vec3 Tangent;
layout (location=4) in vec3 Bitangent;

layout (location=0) out vec3 PositionRight;
layout (location=1) out vec3 PositionLeft;
layout (location=2) out vec3 PositionUp;
layout (location=3) out vec3 PositionBottom;
layout (location=4) out vec3 PositionFront;
layout (location=5) out vec3 PositionBack;

void main() {
    gl_Position     = vec4(Position, 1.0);

    PositionRight   = vec3(-Position.z,  Position.y,  Position.x);
    PositionLeft    = vec3( Position.z,  Position.y,  Position.x);

    PositionUp      = vec3( Position.x, -Position.z,  Position.y);
    PositionBottom  = vec3( Position.x,  Position.z, -Position.y);
    
    PositionFront   = vec3( Position.x,  Position.y,  Position.z);
    PositionBack    = vec3( Position.x,  Position.y, -Position.z);
}