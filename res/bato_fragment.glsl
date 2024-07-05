#version 410

in vec2 uv;
in vec3 pos_normals;
out vec4 output_color;

uniform sampler2D my_texture;
uniform float time_seconds;

void main() {
    // vec4 my_color = texture(my_texture, uv);
    // my_color = vec4(fract(my_color.rgb + time_seconds / 4), 1);

    vec4 my_color = vec4(pos_normals, 1.);
    my_color = vec4(fract(pos_normals + time_seconds / 4), 1.);

    output_color = my_color;
}
