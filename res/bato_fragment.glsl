#version 410

in vec2 uv;
in vec3 pos_normals;
out vec4 output_color;

uniform sampler2D my_texture;
uniform float time_seconds;
uniform vec3 light_direction;

void main() {
    vec4 tex_color = texture(my_texture, uv);

    // Attention à bien normaliser les vecteurs (même les normales 🤯)

    vec3 pos_narmols = normalize(pos_normals);
    vec3 narmol_light = normalize(light_direction);

    // float ndotl = (dot(pos_narmols, narmol_light)); // Lumière directionelle (-1 <> 1)
    float ndotl = clamp(((dot(pos_narmols, - narmol_light) + 1) / 2), 0.3, 1.); // Lumière ambiante (passage à 0 <> 1 puis clamp de 0.3 à 1)

    vec3 my_color = vec3(ndotl * tex_color.xyz);  // - light car on va du bato au soleilllll !

    output_color = vec4(my_color, 1);
}
