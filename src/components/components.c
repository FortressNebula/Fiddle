#include "components.h"
#include <stddef.h>
#include <stdlib.h>

void update_nothing(void *state, Renderer *renderer, Updater *chain_head) {}
void do_nothing(void *state) {}
void free_state(void *state) {free(state);}

Updater empty_updater(void)
{
    Updater updater;
    updater.state = NULL;
    updater.laziness = 0;
    updater.bitmask = 0;
    updater.next = NULL;
    updater.renderer = NULL;
    updater.update = update_nothing;
    updater.destroy = do_nothing;
    return updater;
}

void attach_updater(Updater *chain_head, Updater *updater)
{
    if (updater->update == update_nothing && updater->destroy == do_nothing)
        return;
    
    while (chain_head->next != NULL)
        chain_head = chain_head->next;
    
    chain_head->next = updater;
}

void attach_renderer(Renderer *chain_head, Renderer *renderer)
{
    if (renderer->render == do_nothing && renderer->destroy == do_nothing)
        return;
    
    while (chain_head->next != NULL)
        chain_head = chain_head->next;
    
    chain_head->next = renderer;
}


void destroy_updaters(Updater *chain_head)
{
    if (chain_head->next != NULL)
    {
        destroy_updaters(chain_head->next);
    }
    
    chain_head->destroy(chain_head->state);
}

void destroy_renderers(Renderer *chain_head)
{
    if (chain_head->next != NULL)
    {
        destroy_renderers(chain_head->next);
    }
    
    chain_head->destroy(chain_head->state);
}

Updater* safe_traverse_updaters(Updater *current, int laziness)
{
    if (current->laziness >= laziness) return NULL;
    return current->next;
}