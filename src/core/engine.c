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

void fiddle_update(void* state, Renderer *renderer, Updater *chain_head)
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

    Updater updater;
    updater.laziness = 0;
    updater.next = NULL;
    updater.state = fiddle->window;
    updater.update = fiddle_update;
    updater.destroy = do_nothing;
    fiddle->updater = updater;
    fiddle->updater_chain = &fiddle->updater;

    Renderer renderer;
    renderer.z = 0;
    renderer.next = NULL;
    renderer.state = NULL;
    renderer.render = fiddle_render;
    renderer.destroy = do_nothing;
    fiddle->renderer = renderer;
    fiddle->renderer_chain = &fiddle->renderer;
    fiddle->updater.renderer = &fiddle->renderer;

    return 1;
}


int fiddle_add_object(Fiddle* fiddle, FObject* object)
{
    // attach object to updater and renderer chains
    // only add if run or destroy methods are non-empty
    attach_updater(fiddle->updater_chain, &object->updater);
    attach_renderer(fiddle->renderer_chain, &object->renderer);
}


int fiddle_run(Fiddle* fiddle)
{
    // Run window
    while (!glfwWindowShouldClose(fiddle->window))
    {
        // linked list pointers
        Updater *update_ptr = fiddle->updater_chain;
        Renderer *renderer_ptr = fiddle->renderer_chain;

        // update everything
        while (update_ptr != NULL)
        {
            update_ptr->update(update_ptr->state, update_ptr->renderer, fiddle->updater_chain);
            update_ptr = update_ptr->next;
        }

        // render everything
        while (renderer_ptr != NULL)
        {
            renderer_ptr->render(renderer_ptr->state);
            renderer_ptr = renderer_ptr->next;
        }

        glfwPollEvents();
        glfwSwapBuffers(fiddle->window);
    }

    // Destroy
    destroy_renderers(fiddle->renderer_chain);
    destroy_updaters(fiddle->updater_chain);
    return 0;
}