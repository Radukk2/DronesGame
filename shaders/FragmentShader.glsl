#version 330

precision mediump float;

// Input
in float noiseValue;
in vec3 my_position;

// Output
layout(location = 0) out vec4 out_color;

// Noise Functions
float random (vec2 st) {
    return fract(sin(dot(st.xy, vec2(12.9898,78.233))) * 43758.5453123);
}

float noise(vec2 st) {
    vec2 i = floor(st);
    vec2 f = fract(st);

    float a = random(i);
    float b = random(i + vec2(1.0, 0.0));
    float c = random(i + vec2(0.0, 1.0));
    float d = random(i + vec2(1.0, 1.0));

    vec2 u = f * f * (3.0 - 2.0 * f);

    return mix(a, b, u.x) +
    (c - a) * u.y * (1.0 - u.x) +
    (d - b) * u.x * u.y;
}


void main()
{
    vec3 color1 = vec3(0.1, 0.4, 0.1);
    vec3 color2 = vec3(0, 0.3, 0.0);

    // Generate more detailed noise
    float noiseValue = noise(my_position.xz * 0.5 );
    vec3 blendedColor = mix(color2, color1, noiseValue);

    out_color = vec4(blendedColor, 1.0);
}
