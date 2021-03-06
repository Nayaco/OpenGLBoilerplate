# version 330 core

// code from github.com/wwwtyro/glsl-atmosphere
#define PI 3.141592
#define iSteps 16
#define jSteps 8

vec2 rsi(vec3 r0, vec3 rd, float sr) {
    // ray-sphere intersection that assumes
    // the sphere is centered at the origin.
    // No intersection when result.x > result.y
    float a = dot(rd, rd);
    float b = 2.0 * dot(rd, r0);
    float c = dot(r0, r0) - (sr * sr);
    float d = (b*b) - 4.0*a*c;
    if (d < 0.0) return vec2(1e5,-1e5);
    return vec2(
        (-b - sqrt(d))/(2.0*a),
        (-b + sqrt(d))/(2.0*a)
    );
}
vec3 atmosphere(vec3 r, vec3 r0, vec3 pSun, float iSun, float rPlanet, float rAtmos, vec3 kRlh, float kMie, float shRlh, float shMie, float g) {
    // Normalize the sun and view directions.
    pSun = normalize(pSun);
    r = normalize(r);

    // Calculate the step size of the primary ray.
    vec2 p = rsi(r0, r, rAtmos);
    if (p.x > p.y) return vec3(0,0,0);
    p.y = min(p.y, rsi(r0, r, rPlanet).x);
    float iStepSize = (p.y - p.x) / float(iSteps);
    // Initialize the primary ray time.
    float iTime = 0.0;
    // Initialize accumulators for Rayleigh and Mie scattering.
    vec3 totalRlh = vec3(0,0,0);
    vec3 totalMie = vec3(0,0,0);
    // Initialize optical depth accumulators for the primary ray.
    float iOdRlh = 0.0;
    float iOdMie = 0.0;
    // Calculate the Rayleigh and Mie phases.
    float mu = dot(r, pSun);
    float mumu = mu * mu;
    float gg = g * g;
    float pRlh = 3.0 / (16.0 * PI) * (1.0 + mumu);
    float pMie = 3.0 / (8.0 * PI) * ((1.0 - gg) * (mumu + 1.0)) / (pow(1.0 + gg - 2.0 * mu * g, 1.5) * (2.0 + gg));
    // Sample the primary ray.
    for (int i = 0; i < iSteps; i++) {
        // Calculate the primary ray sample position.
        vec3 iPos = r0 + r * (iTime + iStepSize * 0.5);
        // Calculate the height of the sample.
        float iHeight = length(iPos) - rPlanet;
        // Calculate the optical depth of the Rayleigh and Mie scattering for this step.
        float odStepRlh = exp(-iHeight / shRlh) * iStepSize;
        float odStepMie = exp(-iHeight / shMie) * iStepSize;
        // Accumulate optical depth.
        iOdRlh += odStepRlh;
        iOdMie += odStepMie;
        // Calculate the step size of the secondary ray.
        float jStepSize = rsi(iPos, pSun, rAtmos).y / float(jSteps);
        // Initialize the secondary ray time.
        float jTime = 0.0;
        // Initialize optical depth accumulators for the secondary ray.
        float jOdRlh = 0.0;
        float jOdMie = 0.0;
        // Sample the secondary ray.
        for (int j = 0; j < jSteps; j++) {
            // Calculate the secondary ray sample position.
            vec3 jPos = iPos + pSun * (jTime + jStepSize * 0.5);
            // Calculate the height of the sample.
            float jHeight = length(jPos) - rPlanet;
            // Accumulate the optical depth.
            jOdRlh += exp(-jHeight / shRlh) * jStepSize;
            jOdMie += exp(-jHeight / shMie) * jStepSize;
            // Increment the secondary ray time.
            jTime += jStepSize;
        }
        // Calculate attenuation.
        vec3 attn = exp(-(kMie * (iOdMie + jOdMie) + kRlh * (iOdRlh + jOdRlh)));
        // Accumulate scattering.
        totalRlh += odStepRlh * attn;
        totalMie += odStepMie * attn;
        // Increment the primary ray time.
        iTime += iStepSize;
    }
    // Calculate and return the final color.
    return iSun * (pRlh * kRlh * totalRlh + pMie * kMie * totalMie);
}

// layout (location=0) in vec3 PositionRight;
// layout (location=1) in vec3 PositionLeft;
// layout (location=2) in vec3 PositionUp;
// layout (location=3) in vec3 PositionBottom;
// layout (location=4) in vec3 PositionFront;
// layout (location=5) in vec3 PositionBack;

layout (location=0) out vec4 ColorRight;
layout (location=1) out vec4 ColorLeft;
layout (location=2) out vec4 ColorUp;
layout (location=3) out vec4 ColorBottom;
layout (location=4) out vec4 ColorFront;
layout (location=5) out vec4 ColorBack;

in VS_OUT {
    vec3 PositionRight;
    vec3 PositionLeft;
    vec3 PositionUp;
    vec3 PositionBottom;
    vec3 PositionFront;
    vec3 PositionBack;
} fs_in;

uniform vec3 skymap_sun_pos;
uniform vec3 skymap_sun_color;

vec4 Color(vec3 vPosition) {
    float intensity = 22.0 * length(skymap_sun_color);
    vec3  skymap_color = normalize(skymap_sun_color);

    vec3 color = atmosphere(
        normalize(vPosition),           // normalized ray direction
        vec3(0,6372e3, 0),              // ray origin
        skymap_sun_pos,                 // position of the sun
        intensity,                      // intensity of the sun
        6371e3,                         // radius of the planet in meters
        6471e3,                         // radius of the atmosphere in meters
        vec3(5.5e-6, 13.0e-6, 22.4e-6), // Rayleigh scattering coefficient
        21e-6,                          // Mie scattering coefficient
        8e3,                            // Rayleigh scale height
        1.2e3,                          // Mie scale height
        0.758                           // Mie preferred scattering direction
    );
    color = 1.0 - exp(-1.0 * color);
    return vec4(color, 1.0);
}

void main() {
    ColorRight  = Color(fs_in.PositionRight);
    ColorLeft   = Color(fs_in.PositionLeft);
    ColorUp     = Color(fs_in.PositionUp);
    ColorBottom = Color(fs_in.PositionBottom);
    ColorFront  = Color(fs_in.PositionFront);
    ColorBack   = Color(fs_in.PositionBack);
}