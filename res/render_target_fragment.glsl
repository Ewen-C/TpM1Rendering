#version 410

in vec2 uv;
out vec4 output_color;

uniform sampler2D color_texture;

void main()
{
    vec4 my_color = texture(color_texture, uv);
    output_color = my_color;

    // Post Process !

    // float greyscale = (my_color.r + my_color.g + my_color.b) / 3;
    // output_color = vec4(greyscale, greyscale, greyscale, 1.);

    // float red = my_color.r;
    // output_color = vec4(red, 0, 0, 1.);

    // float fractColorsUni = (fract(my_color.r) + fract(my_color.g) + fract(my_color.b)) / 3;
    // output_color = vec4(fractColorsUni, fractColorsUni, fractColorsUni, 1.);

    // output_color = vec4(fract(my_color.r * 2.5), fract(my_color.g * 2.5), fract(my_color.b * 2.5), 1.);

    // float distance_center = distance(uv , vec2(0.5));
    // output_color = vec4(my_color.rgb * distance_center, 1.);
}
