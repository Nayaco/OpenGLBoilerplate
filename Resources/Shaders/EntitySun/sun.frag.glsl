# version 440 core

layout (location=0) out vec4 FragColor;
layout (location=1) out vec4 Brightness;

// layout (location=2) out vec4 ColorRight;
// layout (location=3) out vec4 ColorLeft;
// layout (location=4) out vec4 ColorUp;
// layout (location=5) out vec4 ColorBack;
// layout (location=6) out vec4 ColorFront

uniform vec3 suncolor;

void main() {
    FragColor = vec4(suncolor, 1.0);
    float brightness = dot(FragColor.rgb, vec3(1.0, 0.7152, 0.0722));
    
    if (brightness > 1.0)
        Brightness = vec4(FragColor.rgb, 1.0);
    else 
        Brightness = vec4(0.0, 0.0, 0.0, 1.0);
}