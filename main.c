#include <stdio.h>
#include "src/engine.h"
#include "src/fobject_makers.h"

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
        0.5f, 0.5f, 0.05f
    };

    FObject triangle;
    if (!static_uncoloured_mesh_fobject(&triangle, sizeof(vertices), vertices, "standard.frag", "standard.vert"))
    {
        printf("Failed to create triangle fobject!");
        return -1;
    }

    fiddle_add_object(&fiddle, &triangle);

    return fiddle_run(&fiddle);
}