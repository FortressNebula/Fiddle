#include <stdio.h>
#include "src/engine.h"
#include "src/components/renderables.h"
#include "src/graphics/shaders.h"

int main(void)
{
    // Init fiddle
    Fiddle fiddle;
    if (!fiddle_init(&fiddle, 800, 600, "Test"))
        return -1;

    // Triangle
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.05f
    };

    // Shader
    unsigned int shader = create_shader_program("standard.frag", "standard.vert");
    if (shader == -1)
        return -1;

    // Create FObject
    FObject triangle;
    triangle.updater = empty_updater();
    triangle.renderer = make_static_renderer();
    elementless_dataless_static_renderable(&triangle.renderer, sizeof(vertices), vertices, shader);

    fiddle_add_object(&fiddle, &triangle);

    return fiddle_run(&fiddle);
}