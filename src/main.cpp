#include "opengl-framework/opengl-framework.hpp" // Inclue la librairie qui va nous servir à faire du rendu

int main()
{
    // Initialisation
    gl::init("TPs de Rendering"); // On crée une fenêtre et on choisit son nom
    gl::maximize_window(); // On peut la maximiser si on veut

    glEnable(GL_BLEND);
    glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE_MINUS_DST_ALPHA, GL_ONE); // On peut configurer l'équation qui mélange deux couleurs, comme pour faire différents blend mode dans Photoshop. Cette équation-ci donne le blending "normal" entre pixels transparents.

    auto const shader_rectangle_background = gl::Shader{{
        .vertex   = gl::ShaderSource::File{"res/vertex_background.glsl"},
        .fragment = gl::ShaderSource::File{"res/fragment_background.glsl"},
    }};

    auto const shader_rectangle_move = gl::Shader{{
        .vertex   = gl::ShaderSource::File{"res/vertex_move.glsl"},
        .fragment = gl::ShaderSource::File{"res/fragment_move.glsl"},
    }};

    // auto const triangle_mesh = gl::Mesh{{
    //     .vertex_buffers = {{
    //         .layout = {gl::VertexAttribute::Position2D{0 /*Index de l'attribut dans le shader, on en reparle juste après*/}},
    //         .data   = {
    //             -0.5f, -0.5f, // Position2D du 1er sommet
    //             +0.5f, -0.5f, // Position2D du 2ème sommet
    //             +0.5f, +0.5f  // Position2D du 3ème sommet
    //         },
    //     }},
    // }};

    auto const rectangle_background = gl::Mesh{{
        .vertex_buffers = {{
            .layout = {gl::VertexAttribute::Position2D{0}},
            .data   = {
                -1, -1, // Position2D du 1er sommet
                +1, -1, // Position2D du 2ème sommet
                +1, +1, // Position2D du 3ème sommet
                -1, +1  // Position2D du 4ème sommet
            },
        }},
        .index_buffer   = {
            0, 1, 2, // Indices du premier triangle : on utilise le 1er, 2ème et 3ème sommet
            0, 2, 3  // Indices du deuxième triangle : on utilise le 1er, 3ème et 4ème sommet
        },
    }};

    auto const rectangle_move = gl::Mesh{{
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

    
    // glClearColor(0, 0.75f, 0, 1.f); // Choisis la couleur à utiliser. Les paramètres sont R, G, B, A avec des valeurs qui vont de 0 à 1
    // glClear(GL_COLOR_BUFFER_BIT); // Exécute concrètement l'action d'appliquer sur tout l'écran la couleur choisie au-dessus

    while (gl::window_is_open())
    {
        
        // // Rendu à chaque frame
        // glClearColor(0, 0.75f, 0, 1.f); // Choisis la couleur à utiliser. Les paramètres sont R, G, B, A avec des valeurs qui vont de 0 à 1
        // glClear(GL_COLOR_BUFFER_BIT); // Exécute concrètement l'action d'appliquer sur tout l'écran la couleur choisie au-dessus

        // C'est ce qu'on appelle un "draw call" : on envoie l'instruction à la carte graphique de dessiner notre mesh.
        // triangle_mesh.draw(); 

        shader_rectangle_background.bind();
        rectangle_background.draw();

        shader_rectangle_move.bind();
        shader_rectangle_move.set_uniform("aspect_ratio", gl::framebuffer_aspect_ratio());
        shader_rectangle_move.set_uniform("time_seconds", gl::time_in_seconds() );
        rectangle_move.draw();
    }
}