#version 330

precision mediump float;

// Input
// TODO(student): Get color value from vertex shader
in vec3 f_color;
in float noiseValue;

// Output
layout(location = 0) out vec4 out_color;

// Functions for noise generation
float random (in vec2 st) {
    return fract(sin(dot(st.xy,
                         vec2(12.9898,78.233)))
                 * 43758.5453123);
}

float noise (in vec2 st) {
    vec2 i = floor(st);
    vec2 f = fract(st);
    float a = random(i);
    float b = random(i + vec2(1.0, 0.0));
    float c = random(i + vec2(0.0, 1.0));
    float d = random(i + vec2(1.0, 1.0));
    vec2 u = f * f * (3.0 - 2.0 * f); // Smootherstep
    return mix(a, b, u.x) +
           (c - a) * u.y * (1.0 - u.x) +
           (d - b) * u.x * u.y;
}

void main()
{
    // Base colors for blending
    vec3 color1 = vec3(0.1, 0.4, 0.1);
    vec3 color2 = vec3(0.0, 0.3, 0.0);
    float smoothFactor = pow(noiseValue, 2.0);
    vec3 blendedColor = mix(f_color, color1, smoothFactor);
    blendedColor = mix(blendedColor, color2, smoothFactor);
    out_color = vec4(abs(blendedColor), 1.0);
}
