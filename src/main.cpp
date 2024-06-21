#include <iostream>;

#include "opengl-framework/opengl-framework.hpp" // Inclue la librairie qui va nous servir à faire du rendu
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"


int main()
{
    // Initialisation

    gl::init("TP de Rendering"); // On crée une fenêtre et on choisit son nom
    gl::maximize_window(); // On peut la maximiser si on veut

    glEnable(GL_BLEND);
    glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE_MINUS_DST_ALPHA, GL_ONE); // On peut configurer l'équation qui mélange deux couleurs, comme pour faire différents blend mode dans Photoshop. Cette équation-ci donne le blending "normal" entre pixels transparents.
    glEnable(GL_DEPTH_TEST);

    // Render target avant camera

    auto render_target = gl::RenderTarget{gl::RenderTarget_Descriptor{
        .width          = gl::framebuffer_width_in_pixels(),
        .height         = gl::framebuffer_height_in_pixels(),
        .color_textures = {
            gl::ColorAttachment_Descriptor{
                .format  = gl::InternalFormat_Color::RGBA8,
                .options = {
                    .minification_filter  = gl::Filter::NearestNeighbour, // On va toujours afficher la texture à la taille de l'écran,
                    .magnification_filter = gl::Filter::NearestNeighbour, // donc les filtres n'auront pas d'effet. Tant qu'à faire on choisit le moins coûteux.
                    .wrap_x               = gl::Wrap::ClampToEdge,
                    .wrap_y               = gl::Wrap::ClampToEdge,
                },
            },
        },
        .depth_stencil_texture = gl::DepthStencilAttachment_Descriptor{
            .format  = gl::InternalFormat_DepthStencil::Depth32F,
            .options = {
                .minification_filter  = gl::Filter::NearestNeighbour,
                .magnification_filter = gl::Filter::NearestNeighbour,
                .wrap_x               = gl::Wrap::ClampToEdge,
                .wrap_y               = gl::Wrap::ClampToEdge,
            },
        },
    }};


    // Setup camera 

    auto camera = gl::Camera{};
    
    gl::set_events_callbacks({
        camera.events_callbacks(),
        {
            // Log la position de la souris
            .on_mouse_pressed = [&](gl::MousePressedEvent const& e) {
                std::cout << "Mouse pressed at " << e.position.x << " " << e.position.y << '\n';
            },
            // Redimensionne la texture dans la render target si la fenêtre est redimensionnée
            .on_framebuffer_resized = [&](gl::FramebufferResizedEvent const& e) {
                render_target.resize(e.width_in_pixels, e.height_in_pixels);
            },
        },
    });


    // Shaders
    
    auto const shader_render_target = gl::Shader{{
        .vertex   = gl::ShaderSource::File{"res/render_target_vertex.glsl"},
        .fragment = gl::ShaderSource::File{"res/render_target_fragment.glsl"},
    }};
    
    auto const my_shader = gl::Shader{{
        .vertex   = gl::ShaderSource::File{"res/vertex_square.glsl"},
        .fragment = gl::ShaderSource::File{"res/fragment_square.glsl"},
    }};

    // Meshes

    auto const mesh_render_target = gl::Mesh{{
        .vertex_buffers = {{
            .layout = {gl::VertexAttribute::Position2D{0}, gl::VertexAttribute::UV{1}},
            .data   = {
                -1, -1, /* Position2D du 1er sommet  */  0, 0, /* UVs du 1er sommet  */
                1, -1, /* Position2D du 2ème sommet */  1, 0, /* UVs du 2ème sommet */
                1, 1, /* Position2D du 3ème sommet */  1, 1, /* UVs du 3ème sommet */
                -1, 1, /* Position2D du 4ème sommet */  0, 1, /* UVs du 4ème sommet */
            },
        }},
        .index_buffer = {
            0, 1, 2, // Indices du premier triangle : on utilise le 1er, 2ème et 3ème sommet
            0, 2, 3  // Indices du deuxième triangle : on utilise le 1er, 3ème et 4ème sommet
        },
    }};

    // auto const square_mesh = gl::Mesh{{
    //     .vertex_buffers = {{
    //         .layout = {gl::VertexAttribute::Position2D{0}, gl::VertexAttribute::UV{1}},
    //         .data   = {
    //             0, 0, /* Position2D du 1er sommet  */  -2, -2, /* UVs du 1er sommet  */
    //             1, 0, /* Position2D du 2ème sommet */  -2, 2 , /* UVs du 2ème sommet */
    //             1, 1, /* Position2D du 3ème sommet */  2 , 2 , /* UVs du 3ème sommet */
    //             0, 1, /* Position2D du 4ème sommet */  2 , -2, /* UVs du 4ème sommet */
    //         },
    //     }},
    //     .index_buffer   = {
    //         0, 1, 2, // Indices du premier triangle : on utilise le 1er, 2ème et 3ème sommet
    //         0, 2, 3  // Indices du deuxième triangle : on utilise le 1er, 3ème et 4ème sommet
    //     },
    // }};

    auto const cube_mesh = gl::Mesh{{
        .vertex_buffers = {{
            .layout = {gl::VertexAttribute::Position3D{0}, gl::VertexAttribute::UV{1}},
            .data   = { // Sommets et UVs
                0, 0, 0,  0, 0,
                1, 0, 0,  0, 1,
                0, 1, 0,  1, 0,
                1, 1, 0,  1, 1,
                
                0, 0, 1,  0, 0,
                1, 0, 1,  0, 1,
                0, 1, 1,  1, 0,
                1, 1, 1,  1, 1,
            },
        }},
        .index_buffer   = { // Triangles des faces utilisant 3 sommets (numéros des sommets ci-dessus commençant à 0)
            0, 1, 2,  1, 2, 3, // Avant
            0, 1, 4,  1, 4, 5, // Dessous
            4, 5, 7,  4, 6, 7, // Arrière
            2, 3, 6,  3, 6, 7, // Dessus
            1, 3, 7,  1, 5, 7, // Côté 1
            2, 0, 4,  2, 6, 4, // Côté 2
        },
    }};

    // Textures

    auto const my_texture = gl::Texture{
        gl::TextureSource::File{ // Peut être un fichier, ou directement un tableau de pixels
            .path           = "res/texture-test.png",
            .flip_y         = true, // Il n'y a pas de convention universelle sur la direction de l'axe Y. Les fichiers (.png, .jpeg) utilisent souvent une direction différente de celle attendue par OpenGL. Ce booléen flip_y est là pour inverser la texture si jamais elle n'apparaît pas dans le bon sens.
            .texture_format = gl::InternalFormat::RGBA8, // Format dans lequel la texture sera stockée. On pourrait par exemple utiliser RGBA16 si on voulait 16 bits par canal de couleur au lieu de 8. (Mais ça ne sert à rien dans notre cas car notre fichier ne contient que 8 bits par canal, donc on ne gagnerait pas de précision). On pourrait aussi stocker en RGB8 si on ne voulait pas de canal alpha. On utilise aussi parfois des textures avec un seul canal (R8) pour des usages spécifiques.
        },
        gl::TextureOptions{
            .minification_filter  = gl::Filter::NearestNeighbour, // Comment on va moyenner les pixels quand on voit l'image de loin ?
            .magnification_filter = gl::Filter::NearestNeighbour, // Comment on va interpoler entre les pixels quand on zoom dans l'image ?
            .wrap_x               = gl::Wrap::ClampToEdge,   // Quelle couleur va-t-on lire si jamais on essaye de lire en dehors de la texture ?
            .wrap_y               = gl::Wrap::ClampToEdge,   // Idem, mais sur l'axe Y. En général on met le même wrap mode sur les deux axes.
        },
    };


    // Draw loop update

    while (gl::window_is_open())
    {
        render_target.render([&]() {

            // Rendu à chaque frame

            glClearColor(0.4f, 0.4f, 0.4f, 1.f); // Choisis la couleur à utiliser. Les paramètres sont R, G, B, A avec des valeurs qui vont de 0 à 1
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Exécute concrètement l'action d'appliquer sur tout l'écran la couleur choisie au-dessus
        
            glm::mat4 const view_matrix = camera.view_matrix();
            glm::mat4 const projection_matrix = glm::infinitePerspective(2.f /*field of view in radians*/, gl::framebuffer_aspect_ratio() /*aspect ratio*/, 0.001f /*near plane*/);
            // glm::mat4 const rotation_matrix = glm::rotate(glm::mat4{1.f}, gl::time_in_seconds() /*angle de la rotation*/, glm::vec3{0.f, 0.f, 1.f} /* axe autour duquel on tourne */);
            // glm::mat4 const translation_matrix = glm::translate(glm::mat4{1.f}, glm::vec3{0.f, 1.f, 0.f} /* déplacement */);
            glm::mat4 const view_projection_matrix = projection_matrix * view_matrix/*  * rotation_matrix * translation_matrix */; // Ordre des opérations des matrices : <-- <-- <--


            // Draw custom mesh

            my_shader.bind();
            my_shader.set_uniform("aspect_ratio", gl::framebuffer_aspect_ratio());
            my_shader.set_uniform("view_projection_matrix", view_projection_matrix);
            my_shader.set_uniform("my_texture", my_texture);

            // square_mesh.draw();
            cube_mesh.draw();

        });
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Exécute concrètement l'action d'appliquer sur tout l'écran la couleur choisie au-dessus

        // Draw render target

        shader_render_target.bind();
        shader_render_target.set_uniform("color_texture", render_target.color_texture(0));

        mesh_render_target.draw();
    }
}
