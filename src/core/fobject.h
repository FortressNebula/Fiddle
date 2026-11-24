#pragma once
#include "chains.h"
#include "graphics/shaders.h"

// Fiddle object
// Includes a renderer, updater, and common state
typedef struct {
    PriorityRunnable updater;
    PriorityRunnable renderer;
} FObject;

// Renderable state with only a VAO and a shader program
typedef struct {
    unsigned int vertices_length;
    unsigned int VAO;
    unsigned int shader_program;
} UniformlessVAORenderableState;