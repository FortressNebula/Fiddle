#pragma once

// FObject Updater component
typedef struct Updater Updater;
// FObject Renderer component
typedef struct Renderer Renderer;

struct Updater {
    // How late the updater updates
    // Lower laziness causes the update and destroy methods to be ran sooner,
    // with negative values happening before the engine itself
    int laziness;
    // User-defined state for the updater
    // Should be freed in the destroy method
    void *state;
    // Pointer to the renderer component of the FObject
    Renderer *renderer;

    // Update the FObject, ran before rendering
    // @param state the state of the updater as defined by the user
    // @param renderer a pointer to the FObject's renderer component
    // @param chain_head a pointer to traverse the updater linked list. ONLY USE SAFE TRAVERSAL!
    void (*update)(void *state, Renderer *renderer, Updater *chain_head);
    // Destroy the FObject, ran after renderer destruction
    // @param state the state of the updater as defined by the user
    void (*destroy)(void *state);

    // Do not touch! Pointer to the next updater in the linked list
    Updater *next;
};

struct Renderer {
    // How late the renderer renders
    // Higher z values render later and above other components,
    // with negative values rendering before the engine itself
    int z;
    // User-defined state for the renderer
    // Should be freed in the destroy method
    void *state;

    // Render the FObject, ran after updating
    // @param state the state of the renderer as defined by the user
    void (*render)(void *state);
    // Destroy the FObject, ran before updater destruction
    // @param state the state of the renderer as defined by the user
    void (*destroy)(void *state);

    // Do not touch! Pointer to the next renderer in the linked list
    Renderer *next;
};

// Dummy updater method
// Assign to an updater's update method if object is static
void update_nothing(void *state, Renderer *renderer, Updater *chain_head);
// Dummy method
// Assign to renderer or updater if object has no state to destroy, or nothing to render
void do_nothing(void *state);
// Dummy updater
// Does and destroys nothing
Updater empty_updater(void);

// Attach an updater to a linked list chain
void attach_updater(Updater *chain_head, Updater *updater);
// Attach a renderer to a linked list chain
void attach_renderer(Renderer *chain_head, Renderer *renderer);

// Destroy an updater linked list chain
void destroy_updaters(Updater *chain_head);
// Destroy a renderer linked list chain
void destroy_renderers(Renderer *chain_head);