#include <iostream>;

#include "opengl-framework/opengl-framework.hpp" // Inclue la librairie qui va nous servir à faire du rendu
#include "glm/ext/matrix_clip_space.hpp"

int main()
{
    // Initialisation
    gl::init("TPs de Rendering"); // On crée une fenêtre et on choisit son nom
    gl::maximize_window(); // On peut la maximiser si on veut

    glEnable(GL_BLEND);
    glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE_MINUS_DST_ALPHA, GL_ONE); // On peut configurer l'équation qui mélange deux couleurs, comme pour faire différents blend mode dans Photoshop. Cette équation-ci donne le blending "normal" entre pixels transparents.

    // Setup camera 
    auto camera = gl::Camera{};
    
    gl::set_events_callbacks({
        camera.events_callbacks(),
        {
            .on_mouse_pressed = [&](gl::MousePressedEvent const& e) {
                std::cout << "Mouse pressed at " << e.position.x << " " << e.position.y << '\n';
            },
        },
    });
    
    auto const shader_square = gl::Shader{{
        .vertex   = gl::ShaderSource::File{"res/vertex_square.glsl"},
        .fragment = gl::ShaderSource::File{"res/fragment_square.glsl"},
    }};

    auto const square_mesh = gl::Mesh{{
        .vertex_buffers = {{
            .layout = {gl::VertexAttribute::Position2D{0}},
            .data   = {
                -0.5f, -0.5f, // Position2D du 1er sommet
                +0.5f, -0.5f, // Position2D du 2ème sommet
                +0.5f, +0.5f, // Position2D du 3ème sommet
                -0.5f, +0.5f  // Position2D du 4ème sommet
            },
        }},
        .index_buffer   = {
            0, 1, 2, // Indices du premier triangle : on utilise le 1er, 2ème et 3ème sommet
            0, 2, 3  // Indices du deuxième triangle : on utilise le 1er, 3ème et 4ème sommet
        },
    }};


    while (gl::window_is_open())
    {
        // Rendu à chaque frame
        glClearColor(0, 0.75f, 0, 1.f); // Choisis la couleur à utiliser. Les paramètres sont R, G, B, A avec des valeurs qui vont de 0 à 1
        glClear(GL_COLOR_BUFFER_BIT); // Exécute concrètement l'action d'appliquer sur tout l'écran la couleur choisie au-dessus
    
        glm::mat4 const view_matrix = camera.view_matrix();

        // glm::mat4 const projection_matrix = glm::infinitePerspective(1.f /*field of view in radians*/, gl::framebuffer_aspect_ratio() /*aspect ratio*/, 0.001f /*near plane*/);
        // glm::mat4 const projection_matrix = glm::infinitePerspective(1.2f /*field of view in radians*/, gl::framebuffer_aspect_ratio() /*aspect ratio*/, 0.02f /*near plane*/);
        glm::mat4 const projection_ortho = glm::ortho(-1.f, 1.f, -1.f, 1.f, 0.1f, 1000.0f);
        
        glm::mat4 const view_projection_matrix = projection_ortho * view_matrix; // Ordre des opérations des matrices : <-- <-- <--

        shader_square.bind();
        shader_square.set_uniform("aspect_ratio", gl::framebuffer_aspect_ratio());
        shader_square.set_uniform("view_projection_matrix", view_projection_matrix);

        square_mesh.draw();
    }
}
