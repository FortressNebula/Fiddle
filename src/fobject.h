#pragma once
#include "components/components.h"

// Fiddle object
// Includes a renderer, updater, and common state
typedef struct {
    Updater updater;
    Renderer renderer;
} FObject;