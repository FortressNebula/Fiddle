#include "fobject_makers.h"
#include "graphics/shaders.h"
#include <stdio.h>
#include <stdlib.h>

static void draw_uncoloured_mesh_fobject(void* state)
{
    UniformlessVAORenderableState* renderable = state;
    glBindVertexArray(renderable->VAO);
    glUseProgram(renderable->shader_program);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

static void destroy_uncoloured_mesh_fobject(void* renderer_state)
{
    UniformlessVAORenderableState* renderable = renderer_state;
    free(renderable);
}

int static_uncoloured_mesh_fobject(FObject *object, int sizeof_vertices, float vertices[], char* frag_shader_path, char* vert_shader_path)
{
    // Create updater
    object->updater = empty_updater();

    // Create state
    UniformlessVAORenderableState* state = malloc(sizeof(*state));
    // Create VAO
    unsigned int VAO;
    unsigned int VBO;   
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    // Bind VBO and configure
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof_vertices, vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), 0);
    glEnableVertexAttribArray(0);
    // Create shader program
    unsigned int program = create_shader_program(frag_shader_path, vert_shader_path);
    if (program == -1)
    {
        printf("Failed to create fobject");
        return 0;
    }
    // Bind to state
    state->VAO = VAO;
    state->shader_program = program;
    state->vertices_length = sizeof_vertices / (3 * sizeof(float));

    // Create renderer
    Renderer renderer;
    renderer.state = state;
    renderer.z = 1;
    renderer.next = NULL;
    renderer.render = draw_uncoloured_mesh_fobject;
    renderer.destroy = destroy_uncoloured_mesh_fobject;
    object->renderer = renderer;

    return 1;
}