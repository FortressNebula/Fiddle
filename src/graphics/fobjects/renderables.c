#include "renderables.h"
#include <glad/glad.h>

void elementless_dataless_static_renderable(StaticRenderable *renderable, int sizeof_vertices, float vertices[], unsigned int shader)
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
    renderable->VAO = VAO;
    renderable->shader_program = shader;
    renderable->vertices_length = sizeof_vertices;
}