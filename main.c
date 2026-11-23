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


void render(GLFWwindow *window)
{
    glClearColor(0.1f, 0.3f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}


int main(void)
{
    // Create window
    GLFWwindow *window = make_window(800, 600, "Test");
    if (!window) return -1; 

    unsigned int standard_program = create_shader_program("standard.frag", "standard.vert");
    glUseProgram(standard_program);

    // Run window
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        render(window);

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}