#include "renderables.h"
#include <glad/glad.h>
#include <stddef.h>
#include <stdlib.h>

// Static renderables
static void draw_static_renderable(void* state)
{
    StaticRenderable *renderable  = state;
    glBindVertexArray(renderable->VAO);
    glUseProgram(renderable->shader_program);
    glDrawArrays(GL_TRIANGLES, 0, renderable->vertices_length);
}


Renderer make_static_renderer(void)
{
    Renderer renderer;
    renderer.z = 0;
    renderer.next = NULL;
    renderer.render = draw_static_renderable;
    renderer.destroy = free_state;
    return renderer;
}


void elementless_dataless_static_renderable(Renderer *renderer, int sizeof_vertices, float vertices[], unsigned int shader)
{
    unsigned int VAO;
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // dump vertex data in
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof_vertices, vertices, GL_STATIC_DRAW);

    // set up vert attrs
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // set up renderable
    StaticRenderable* renderable = malloc(sizeof(StaticRenderable));
    renderable->VAO = VAO;
    renderable->shader_program = shader;
    renderable->vertices_length = sizeof_vertices / (3 * sizeof(float));
    renderer->state = renderable;
}