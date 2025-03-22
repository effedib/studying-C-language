#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <convertRomanNumber.h>
#include <tokenize.h>
#include <quantity.h>

quantity *createQuantity(quantity **head, char *qu, char *value)
{
    quantity *i = malloc(sizeof(quantity));
    i->quantity = strdup(qu);
    i->roman = strdup(value);
    i->next = *head;
    *head = i;

    return i;
}

quantity *addQuantity(quantity **head, char *qu, char *unit)
{
    quantity *tmp = *head;
    while (tmp != NULL)
    {
        if (strcmp(tmp->quantity, qu) == 0)
        {
            free(tmp->roman);
            tmp->roman = strdup(unit);
            return tmp;
        }
        tmp = tmp->next;
    }
    return createQuantity(head, qu, unit);
}

void releaseQuantity(quantity *q)
{
    while (q != NULL)
    {
        quantity *qtemp = q;
        q = q->next;

        if (qtemp->quantity)
            free(qtemp->quantity);
        if (qtemp->roman)
            free(qtemp->roman);
        free(qtemp);
    }
}
