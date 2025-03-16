#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "convertRomanNumber.h"

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

void releaseItem(item *i)
{
    if (i)
    {
        if (i->next)
            releaseItem(i->next);
        // if (i->item)
        //     free(i->item);
        free(i);
    }
}

int main()
{
    char str[80];
    puts("Enter the input (BLANK to quit):");
    fgets(str, sizeof(str), stdin);
    str[strcspn(str, "\n")] = '\0';

    char *delimiters = " is ";
    char *token;
    char *prefix = NULL;
    char *suffix = NULL;

    token = strstr(str, delimiters);
    if (token != NULL)
    {
        *token = '\0';
        prefix = str;
        printf("prefix: %s\n", prefix);

        suffix = token + strlen(delimiters);
        printf("sufffix: %s\n", suffix);

        int num1 = convertRomanNumber(suffix);
        item *glob = create_item(prefix, num1);
        printf("%s is %i\n", glob->item, glob->unit);
        releaseItem(glob);
    }
}