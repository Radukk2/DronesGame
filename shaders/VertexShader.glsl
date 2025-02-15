#version 330

// Input attributes
layout (location = 0) in vec3 position;      // Vertex position
layout (location = 1) in vec3 normal;        // Texture coordinates
layout (location = 3) in vec3 color;         // Vertex color

// Uniforms
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform float Time; // Optional: can be used for time-based animations

out vec3 my_position;

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
    // TODO(student): Send output to fragment shader
    float frequency = 0.18;
    float amplitude = 0.18;
    my_position = position;
    my_position.y += noise(my_position.xz * frequency);
    // f_color = color;
    gl_Position = Projection * View * (Model * vec4(my_position, 1.0));

}
