#version 410

layout(location = 0) in vec2 in_position;

// Vous pouvez mettre le type que vous voulez, et le nom que vous voulez
uniform float aspect_ratio; 
uniform float time_seconds;
uniform float speed = 0.5;

void main()
{
    vec2 my_position = in_position;
    my_position.x /= aspect_ratio; // Ractange -> Carré

    my_position.x += cos(time_seconds) * speed;
    my_position.y += sin(time_seconds) * speed;

    gl_Position = vec4(my_position, 0., 1.);
}