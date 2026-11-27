#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "components/components.h"
#include "fobject.h"

// Instance of Fiddle
typedef struct {
    // Name of the window
    char name[256];
    // Size of the window
    int width, height;

    // The engine's own updater function and state. Do not touch!
    Updater updater;
    // The engine's own renderer function and state. Do not touch!
    Renderer renderer;
    
    // Head of the updater chain linked list
    Updater *updater_chain;
    // Head of the renderer chain linkde list
    Renderer *renderer_chain;
    // GLFW window pointer
    GLFWwindow *window;
} Fiddle;

// Initialise Fiddle with the given parameters
// @param fiddle a pointer to your instance of Fiddle
// @param width width of the window
// @param height height of the window
// @param name name of the window
// @returns 1 if the initialisation succeeded, or else 0
int fiddle_init(Fiddle *fiddle, int width, int height, char* name);
// Run fiddle
// @param fiddle a pointer to your instance of Fiddle
// @returns 0 if the program succeeded, or else -1
int fiddle_run(Fiddle *fiddle);

// Attach a FObject to the Fiddle instance
// @param fiddle a pointer to your instance of fiddle
// @param object a pointer to your FObject
// @returns 1 if the attachment succeeded, or else 0
int fiddle_add_object(Fiddle *fiddle, FObject *object);
