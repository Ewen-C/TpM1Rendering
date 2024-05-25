#version 410

layout(location = 0) in vec3 in_position;

// Vous pouvez mettre le type que vous voulez, et le nom que vous voulez
uniform float aspect_ratio;
uniform mat4 view_projection_matrix;
    
out vec3 vertex_position;

void main()
{
    vec3 my_position = in_position;
    my_position /= aspect_ratio; // Rectangle -> Carré

    // gl_Position = vec4(my_position, 0., 1.);
    gl_Position = view_projection_matrix * vec4(my_position, 1.);

    vertex_position = in_position;
}
