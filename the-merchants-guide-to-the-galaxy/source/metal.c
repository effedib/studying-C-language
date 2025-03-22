#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <quantity.h>
#include <tokenize.h>
#include <metal.h>

metal *createMetal(metal **head, char *met, float cost)
{
    metal *m = malloc(sizeof(metal));
    m->metal = strdup(met);
    m->cost = cost;
    m->next = *head;
    *head = m;

    return m;
}

metal *addMetal(metal **head, char *met, float cost)
{
    metal *tmp = *head;
    while (tmp != NULL)
    {
        if (strcmp(tmp->metal, met) == 0)
        {
            tmp->cost = cost;
            return tmp;
        }
        tmp = tmp->next;
    }
    return createMetal(head, met, cost);
}

void releaseMetal(metal *m)
{
    if (m)
    {
        if (m->next)
            releaseMetal(m->next);
        if (m->metal)
            free(m->metal);
        free(m);
    }
}