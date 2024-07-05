#version 410

// in vec2 vertex_position; // square
// in vec3 vertex_position; // cube

in vec2 uv;
out vec4 output_color;

uniform sampler2D my_texture;
uniform float time_seconds;

void main() {
    // out_color = vec4(uv.x, uv.y, 0., 1.);

    // out_color = vec4(vertex_position, 0., 1.); // square
    // out_color = vec4(vertex_position, 0., 1.); // cube

    // output_color = texture(my_texture, uv);

    vec4 my_color = texture(my_texture, uv);
    // my_color = vec4(fract(my_color.rgb + time_seconds / 4), 1);

    output_color = my_color;
}
