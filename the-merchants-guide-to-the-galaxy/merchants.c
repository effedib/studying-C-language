#include <stdio.h>
#include <string.h>
#include <regex.h>
#include <stdlib.h>
#include "convertRomanNumber.h"

typedef struct tokenArray
{
    char **tokens;
    int count;
} tokenArray;

typedef struct quantity
{
    char *quantity;
    char *roman;
    struct quantity *next;
} quantity;

typedef struct metal
{
    char *metal;
    float cost;
    struct metal *next;
} metal;

tokenArray *tokenize(char *input)
{
    tokenArray *t = malloc(sizeof(tokenArray));
    t->tokens = NULL;
    t->count = 0;
    char *copy = strdup(input);
    char *countCopy = strdup(input);
    const char delimiters[] = " .,;:!?-";

    int count = 0;
    char *token = strtok(countCopy, delimiters);
    while (token != NULL)
    {
        count++;
        token = strtok(NULL, delimiters);
    }
    free(countCopy);

    t->tokens = malloc(count * sizeof(char *));
    t->count = count;

    token = strtok(copy, delimiters);
    for (int i = 0; i < count && token != NULL; i++)
    {
        t->tokens[i] = strdup(token);
        token = strtok(NULL, delimiters);
    }

    free(copy);

    return t;
}

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

void releaseTokens(tokenArray *t)
{
    if (t)
    {
        for (int i = 0; i < t->count; i++)
            free(t->tokens[i]);
        free(t->tokens);
        free(t);
        t = NULL;
    }
}

int split(tokenArray *tokens, tokenArray **prefix, tokenArray **suffix)
{

    tokenArray *prfx = malloc(sizeof(tokenArray));
    prfx->tokens = NULL;
    prfx->count = 0;
    *prefix = prfx;

    tokenArray *sffx = malloc(sizeof(tokenArray));
    sffx->tokens = NULL;
    sffx->count = 0;
    *suffix = sffx;

    int delimIndex = -1;
    for (int i = 0; i < tokens->count; i++)
        if ((strcmp(tokens->tokens[i], "is") == 0) ||
            (strcmp(tokens->tokens[i], "are") == 0))
        {
            delimIndex = i;
            break;
        }

    if (delimIndex == -1)
        return -1;

    prfx->count = delimIndex;
    if (prfx->count > 0)
    {
        prfx->tokens = malloc(prfx->count * sizeof(char *));
        for (int i = 0; i < prfx->count; i++)
            prfx->tokens[i] = strdup(tokens->tokens[i]);
    }

    sffx->count = tokens->count - delimIndex - 1;
    if (sffx->count > 0)
    {
        sffx->tokens = malloc(sffx->count * sizeof(char *));
        for (int i = 0; i < sffx->count; i++)
            sffx->tokens[i] = strdup(tokens->tokens[delimIndex + 1 + i]);
    }

    return delimIndex;
}

int sumQuantity(quantity *q, tokenArray *t)
{
    quantity *qtemp = q;
    int length = t->count;
    int counter = 0;

    char *finalString = (char *)malloc((length + 1) * sizeof(char));
    if (finalString == NULL)
    {
        printf("Errore di allocazione della memoria\n");
        exit(1);
    }

    for (int i = 0; i < length; i++)
    {
        while (qtemp != NULL)
        {
            if (strcmp(t->tokens[i], qtemp->quantity) == 0)
            {
                finalString[i] = *qtemp->roman;
                counter++;
                break;
            }
            else
                qtemp = qtemp->next;
        }
        qtemp = q;
    }
    finalString[counter] = '\0';

    int sum = convertRomanNumber(finalString);
    free(finalString);
    return sum;
}

metal *checkMetal(tokenArray *prefix, tokenArray *suffix, metal **m, quantity *q)
{
    float totalCost, costPerMetal;
    int units = 0;
    char *endptr;

    totalCost = strtof(suffix->tokens[0], &endptr);

    if (endptr == suffix->tokens[0])
        return NULL;

    units = sumQuantity(q, prefix);
    if (units <= 0)
    {
        printf("Some quantity is not recognized\n");
        return NULL;
    }
    costPerMetal = totalCost / units;
    char *metalToCheck = prefix->tokens[prefix->count - 1];
    metal *newMetal = addMetal(m, metalToCheck, costPerMetal);

    return newMetal;
}

float countMetal(tokenArray *t, metal *mhead, quantity *qhead)
{
    float credits = 0.0;
    int units = 0;
    char *metalstring = t->tokens[t->count - 1];
    metal *mtemp = mhead;

    while ((strcmp(mtemp->metal, metalstring) != 0) && (mtemp->next != NULL))
        mtemp = mtemp->next;

    if ((strcmp(mtemp->metal, metalstring) != 0))
        return credits;

    credits = mtemp->cost;
    units = sumQuantity(qhead, t);
    credits *= units;

    return credits;
}

int matchPattern(const char *string, const char *pattern)
{
    regex_t regex;
    int reti;

    reti = regcomp(&regex, pattern, REG_EXTENDED);
    if (reti)
        fprintf(stderr, "Could not compile regex\n");

    reti = regexec(&regex, string, 0, NULL, 0);

    regfree(&regex);

    return reti;
}

int main()
{
    char str[80];
    tokenArray *t = NULL, *prefix = NULL, *suffix = NULL;
    quantity *qhead = NULL;
    metal *mhead = NULL;
    float credits = 0.0;
    int units = 0, unit = 0;

    while (1)
    {
        puts("Enter the input (press ENTER to quit):");
        fgets(str, sizeof(str), stdin);
        str[strcspn(str, "\n")] = '\0';

        if (strcmp(str, "") == 0)
            break;

        t = tokenize(str);
        split(t, &prefix, &suffix);

        if (unit = convertRomanNumber(suffix->tokens[suffix->count - 1]) > 0)
        {
            quantity *qtemp = addQuantity(&qhead, prefix->tokens[0], suffix->tokens[0]);
            printf("%s => %i\n", qtemp->quantity, unit);
        }
        else if (matchPattern(str, "credits$") == 0)
        {
            metal *mtemp = checkMetal(prefix, suffix, &mhead, qhead);
            if (mtemp)
                printf("Cost: %s => %.2f per unit\n", mtemp->metal, mtemp->cost);
        }
        else if (matchPattern(str, "^how much") == 0)
        {
            units = sumQuantity(qhead, suffix);
            printf("Result: %i\n", units);
        }
        else if (matchPattern(str, "^how many credits") == 0)
        {
            credits = countMetal(suffix, mhead, qhead);
            printf("%.2f credits => metal: %s\n", credits, suffix->tokens[suffix->count - 1]);
        }
        else
            puts("Wrong input!");

        releaseTokens(t);
        releaseTokens(prefix);
        releaseTokens(suffix);

        putchar('\n');
    }

    releaseQuantity(qhead);
    releaseMetal(mhead);
}