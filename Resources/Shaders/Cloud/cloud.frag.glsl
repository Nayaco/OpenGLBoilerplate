# version 330 core

layout (location=0) out vec4 FragColor;
// layout (location=1) out vec4 ColorLeft;

in vec2 ColorTexCoord;

uniform sampler2D cloud_textureA;
uniform sampler2D cloud_textureB;
uniform sampler2D cloud_textureC;
uniform sampler2D cloud_textureD;

uniform float offset_x;
uniform float offset_z;

void main() {
    vec3 cloudparam;
    
    if (ColorTexCoord.x <= 0.5 && ColorTexCoord.y <= 0.5) {
        cloudparam =
            texture(cloud_textureA, ColorTexCoord + vec2(0.5, 0.5)).rbg;
            //texture(cloud_textureA, ColorTexCoord * 2.0).r;// + vec2(0.5, 0.5)).r;
    } 
    else if (ColorTexCoord.x > 0.5 && ColorTexCoord.y <= 0.5) {
        cloudparam = 
            texture(cloud_textureB, ColorTexCoord + vec2(-0.5, 0.5)).rbg;
            //texture(cloud_textureB, (ColorTexCoord - vec2(0.5, 0.0)) * 2.0).r;// + vec2(0.0, 0.5)).r;
    } 
    else if (ColorTexCoord.x <= 0.5 && ColorTexCoord.y > 0.5) {
        cloudparam = 
            texture(cloud_textureC, ColorTexCoord + vec2(0.5, -0.5)).rbg;
            // texture(cloud_textureC, (ColorTexCoord - vec2(0.0, 0.5)) * 2.0).r;//+ vec2(0.5, 0.0)).r;
    } 
    else {
        cloudparam = 
            texture(cloud_textureD, ColorTexCoord + vec2(-0.5, -0.5)).rbg;
            // texture(cloud_textureD, (ColorTexCoord - vec2(0.5, 0.5)) * 2.0).r;// + vec2(0.0, 0.0)).r;
    }
    if (cloudparam.r < 0.5) 
        FragColor = vec4(0.0, 0.0, 0.0, 1.0);
    else if(cloudparam.r < 0.6)
        FragColor = vec4(cloudparam / 1.2, 1.0);
    else 
        FragColor = vec4(cloudparam, 1.0);
}
