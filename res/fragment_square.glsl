#version 410

// in vec2 vertex_position; // square
// in vec3 vertex_position; // cube

// out vec4 out_color;

in vec2 uv;

out vec4 texture_color;

uniform sampler2D my_texture;

void main()
{
    // out_color = vec4(uv.x, uv.y, 0., 1.);
    
    // out_color = vec4(vertex_position, 0., 1.); // square
    // out_color = vec4(vertex_position, 0., 1.); // cube

    texture_color = texture(my_texture, uv);
}
