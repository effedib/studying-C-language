#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "convertRoman2Int.h"

typedef struct item
{
    char *item;
    int unit;
    struct item *next;
} item;

item *create_item(char *inputStr, int count)
{
    item *i = malloc(sizeof(item));
    i->item = inputStr;
    i->unit = count;
    i->next = NULL;

    return i;
}

void release(item *i)
{
    if (i)
    {
        if (i->next)
            release(i->next);
        // if (i->item)
        //     free(i->item);
        free(i);
    }
}

int main()
{
    char *g = "glob";
    char *i = "V";
    int num1 = convertRoman2Int(i);
    item *glob = create_item(g, num1);
    printf("%s is %i\n", glob->item, glob->unit);

    char *p = "prok";
    int num2 = 2;
    glob->next = create_item(p, num2);
    printf("%s is %i\n", glob->next->item, glob->next->unit);

    release(glob);
}