#version 410

// layout : fonctions utilisant les .data dans l'ordre donné (il doit y avoir assez de valeurs dans le .data)
// Seul le vertex shader a accès au layout

layout(location = 0) in vec3 in_position;
out vec3 vertex_position;

layout(location = 1) in vec2 uv_in;
out vec2 uv;

layout(location = 2) in vec3 in_normals;
out vec3 tex_normals;

// uniform : variables envoyée du C++ au shaders
uniform float aspect_ratio;
uniform mat4 view_projection_matrix;
uniform mat4 rotation_matrix;

vec3 apply_matrix_to_position(mat4 matrix, vec3 point) {
    vec4 tmp = matrix * vec4(point, 1.);
    return tmp.xyz / tmp.w;
}

vec3 apply_matrix_to_direction(mat4 matrix, vec3 direction) {
    vec4 tmp = matrix * vec4(direction, 0.);
    return normalize(tmp.xyz);
}

void main() {
    vec3 my_position = in_position; // cube

    my_position /= aspect_ratio; // Rectangle -> Carré

    gl_Position = view_projection_matrix * vec4(my_position, 1.); // cube

    vertex_position = apply_matrix_to_position(rotation_matrix, in_position);
    uv = uv_in;
    tex_normals = apply_matrix_to_direction(rotation_matrix, in_normals);
}
