#include "engine.h"
#include <stdio.h>
#include <string.h>

#pragma region boilerplate
static void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}  


static GLFWwindow* make_window(int width, int height, char* name)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(width, height, name, NULL, NULL);
    if (window == NULL)
    {
        printf("Failed to initialise GLFW!\n");
        glfwTerminate();
        return NULL;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printf("Failed to initialise GLAD!\n");
        glfwTerminate();
        return NULL;
    }

    glViewport(0, 0, width, height);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    return window;
}
#pragma endregion

void fiddle_update(void* state)
{
    GLFWwindow* window = state;
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, 1);
    }
    return;
}

void fiddle_render(void* state)
{
    glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

int fiddle_init(Fiddle *fiddle, int width, int height, char* name)
{
    strcpy(fiddle->name, name);
    fiddle->width = width;
    fiddle->height = height;

    fiddle->window = make_window(width, height, name);
    if (fiddle->window == NULL)
    {
        printf("Failed to initialise Fiddle\n");
        return 0;
    }

    PriorityRunnable updater;
    updater.z_index = 0;
    updater.next = NULL;
    updater.state = fiddle->window;
    updater.run = fiddle_update;
    updater.destroy = do_nothing;
    fiddle->updater = updater;
    fiddle->updater_chain = &fiddle->updater;

    PriorityRunnable renderer;
    renderer.z_index = 0;
    renderer.next = NULL;
    renderer.state = NULL;
    renderer.run = fiddle_render;
    renderer.destroy = do_nothing;
    fiddle->renderer = renderer;
    fiddle->renderer_chain = &fiddle->renderer;

    return 1;
}


int fiddle_add_object(Fiddle* fiddle, FObject* object)
{
    // attach object to updater and renderer chains
    // only add if run or destroy methods are non-empty
    if (object->updater.run != do_nothing || object->updater.destroy != do_nothing)
        attach_runnable(fiddle->updater_chain, &object->updater);
    if (object->renderer.run != do_nothing || object->renderer.destroy != do_nothing)
        attach_runnable(fiddle->renderer_chain, &object->renderer);
}


int fiddle_run(Fiddle* fiddle)
{
    // Run window
    while (!glfwWindowShouldClose(fiddle->window))
    {
        run_priority_runnable_chain(fiddle->updater_chain);
        run_priority_runnable_chain(fiddle->renderer_chain);

        glfwPollEvents();
        glfwSwapBuffers(fiddle->window);
    }

    // Destroy
    destroy_priority_runnable_chain(fiddle->renderer_chain);
    destroy_priority_runnable_chain(fiddle->updater_chain);
    glfwTerminate();
    return 0;
}