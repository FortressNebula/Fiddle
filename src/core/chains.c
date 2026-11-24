#include "chains.h"
#include <stddef.h>
#include <stdio.h>

void attach_runnable(PriorityRunnable *head, PriorityRunnable *val)
{
    while (head->next != NULL)
        head = head->next;
    
    head->next = val;
}

void run_priority_runnable_chain(PriorityRunnable *head)
{
    while (head != NULL)
    {
        head->run(head->state);
        head = head->next;
    }
}

void destroy_priority_runnable_chain(PriorityRunnable *head)
{
    if (head->next != NULL)
    {
        destroy_priority_runnable_chain(head->next);
    }
    
    head->destroy(head->state);
}

void do_nothing(void* state) {state;}