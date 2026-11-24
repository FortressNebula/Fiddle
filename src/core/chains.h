#pragma once

// Struct defining either an updater or a renderer
// Object is given a z index, where a smaller z value is processed first
// Corresponds to a literal z value in the renderer
// Corresponds to a "logical" z value in the updater
// Negative values will be carried out before the engine
typedef struct PriorityRunnable PriorityRunnable;

struct PriorityRunnable {
    int z_index;
    void (*run)(void* state);
    void (*destroy)(void* state);
    void *state;
    PriorityRunnable *next;
};

// Add a runnable "val" to the runnable chain starting at "head"
void attach_runnable(PriorityRunnable *head, PriorityRunnable *val);
// Run the whole runnable chain
void run_priority_runnable_chain(PriorityRunnable *head);
// Destroy the whole runnable chain
void destroy_priority_runnable_chain(PriorityRunnable *head);
// Do nothing dummy method
void do_nothing(void* state);