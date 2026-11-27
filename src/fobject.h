#pragma once
#include "components.h"
#include "graphics/shaders.h"

// Fiddle object
// Includes a renderer, updater, and common state
typedef struct {
    Updater updater;
    Renderer renderer;
} FObject;