#version 330
precision mediump float;
// Input
// TODO(student): Get vertex attributes from each location
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;
layout(location = 2)in vec3 normal;



// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

// Output
out vec3 f_color;
out float noiseValue;
// TODO(student): Output values to fragment shader

// 2D Random
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
    vec2 u = f*f*(3.0-2.0*f);
    return mix(a, b, u.x) +
            (c - a)* u.y * (1.0 - u.x) +
            (d - b) * u.x * u.y;
}

void main()
{
    // TODO(student): Send output to fragment shader
    float frequency = 0.1;
    float amplitude = 1.1;
    vec3 my_position = position;
    noiseValue = noise(my_position.xz);
    my_position.y += noise(my_position.xz * frequency) * amplitude;
    f_color = color;
    gl_Position = Projection * View * (Model * vec4(my_position, 1.0));

}
