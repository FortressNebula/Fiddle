#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "chains.h"
#include "fobject.h"

typedef struct {
    char name[256];
    int width, height;

    PriorityRunnable updater;
    PriorityRunnable renderer;

    PriorityRunnable *updater_chain;
    PriorityRunnable *renderer_chain;
    GLFWwindow *window;
} Fiddle;

// Initialise Fiddle
// Returns a pointer to the Fiddle Instance
int fiddle_init(Fiddle *fiddle, int width, int height, char* name);
// Run fiddle
int fiddle_run(Fiddle *fiddle);

// Attach a FObject to the Fiddle instance
int fiddle_add_object(Fiddle *fiddle, FObject *object);
