#version 410

in vec2 uv;
in vec3 pos_normals;
out vec4 output_color;

uniform sampler2D my_texture;
uniform float time_seconds;
uniform vec3 light_direction;

void main() {
    vec4 tex_color = texture(my_texture, uv);

    vec3 pos_narmols = normalize(pos_normals);
    vec3 narmol_light = normalize(- light_direction); // - light car on va du bato au soleilllll !

    float ndotl = (dot(pos_narmols, narmol_light) + 1) / 2;
    vec3 my_color = vec3(ndotl * tex_color.xyz);

    output_color = vec4(my_color, 1);
}
