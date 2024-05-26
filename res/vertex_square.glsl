#version 410

layout(location = 0) in vec2 in_position; // square
// layout(location = 0) in vec3 in_position; // cube

uniform float aspect_ratio;
uniform mat4 view_projection_matrix;
    
out vec2 vertex_position;  // square
// out vec3 vertex_position;  // cube

layout(location = 1) in vec2 uv_in;
out vec2 uv;

void main()
{
    vec2 my_position = in_position; // squares
    // vec3 my_position = in_position; // cube

    my_position /= aspect_ratio; // Rectangle -> Carré

    gl_Position = view_projection_matrix * vec4(my_position, 0., 1.); // square
    // gl_Position = view_projection_matrix * vec4(my_position, 1.); // cube

    vertex_position = in_position;

    uv = uv_in;
}
