#version 410

// layout : fonctions utilisant les .data dans l'ordre donné (il doit y avoir assez de valeurs dans le .data)
// Seul le vertex shader a accès au layout

layout(location = 0) in vec2 in_position; // square
layout(location = 1) in vec2 uv_in;

out vec2 uv;

void main()
{
    gl_Position = vec4(in_position, 0, 1.0); // square
    uv = uv_in;
}
