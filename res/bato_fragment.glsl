#version 410

in vec3 vertex_position;
in vec2 uv;
in vec3 tex_normals;
out vec4 output_color;

uniform sampler2D my_texture;
uniform float time_seconds;

uniform vec3 light_direction;
uniform vec3 light_position;
uniform float light_intensity;

void main() {
    vec4 tex_color = texture(my_texture, uv);

    // Attention à bien normaliser les vecteurs (même les normales 🤯)

    vec3 pos_narmols = normalize(tex_normals);
    vec3 narmol_light_dir = normalize(light_direction);

    vec3 narmol_light_pos = normalize(light_position);

    // float ndotl = dot(pos_narmols, narmol_light_dir); // Lumière directionelle (-1 <> 1)
    // float ndotl = clamp(((dot(pos_narmols, - narmol_light_dir) + 1) / 2), 0.3, 1.); // Lumière ambiante (passage à 0 <> 1 puis clamp de 0.3 à 1)

    float dist_light = distance(pos_narmols, light_position); // Lumière ponctuelle
    float ndotl = dot(vertex_position, light_position) * light_intensity;

    vec3 my_color = vec3(- ndotl * tex_color.xyz);  // - light car on va du bato au soleilllll !
    my_color = my_color / (dist_light * dist_light);

    output_color = vec4(my_color, 1);
}
