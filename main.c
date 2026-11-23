#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "src/engine.h"
#include "src/shaders.h"


void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, 1);
    }
}



int main(void)
{
    // Create window
    GLFWwindow *window = make_window(800, 600, "Test");
    if (!window) return -1; 

    unsigned int standard_program = create_shader_program("standard.frag", "standard.vert");

    // Triangle
    float triangle[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.5f, 0.5f, 0.05f
    };

    // Create vertex array object for triangle
    unsigned int triangle_VAO;
    unsigned int triangle_VBO;
    glGenBuffers(1, &triangle_VBO);
    glGenVertexArrays(1, &triangle_VAO);
    glBindVertexArray(triangle_VAO);

    // Bind VBO and configure
    glBindBuffer(GL_ARRAY_BUFFER, triangle_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), 0);
    glEnableVertexAttribArray(0);

    // Run window
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.1f, 0.3f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw triangle
        glUseProgram(standard_program);
        glBindVertexArray(triangle_VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}