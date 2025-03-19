#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "convertRomanNumber.h"

typedef struct quantity
{
    char *quantity;
    int unit;
    struct quantity *next;
} quantity;

typedef struct metal
{
    char *metal;
    float cost;
    struct metal *next;
} metal;

typedef struct token
{
    char *token;
    struct token *next;
} token;

void printQuantityList(quantity *q);
void printMetalList(metal *m);
void printTokenList(token *t);

quantity *addQuantity(quantity **head, char *inputStr, int count)
{
    quantity *i = malloc(sizeof(quantity));
    i->quantity = strdup(inputStr);
    i->unit = count;
    i->next = *head;
    *head = i;

    printf("%s = %i\n", i->quantity, i->unit);

    return i;
}

void releaseQuantity(quantity *q)
{
    if (q)
    {
        if (q->next)
            releaseQuantity(q->next);
        if (q->quantity)
            free(q->quantity);
        free(q);
    }
}

int findQuantity(quantity *q, char *inputQuantity)
{
    if (q)
    {
        if (strcmp(q->quantity, inputQuantity) == 0)
            return q->unit;
        return findQuantity(q->next, inputQuantity);
    }
    return 0;
}

metal *addMetal(metal **head, char *stringMetal, float cost)
{
    metal *m = malloc(sizeof(metal));
    m->metal = strdup(stringMetal);
    m->cost = cost;
    m->next = *head;
    *head = m;

    return m;
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

token *createToken(char *t)
{
    token *newToken = malloc(sizeof(token));
    newToken->token = strdup(t);
    newToken->next = NULL;

    return newToken;
}

token *tokenizer(char *string)
{
    char *tok, *copy;
    const char delimiters[] = " .,;:!-";
    token *thead = NULL;

    copy = strdup(string);
    tok = strtok(copy, delimiters);
    while (tok != NULL)
    {
        token *newToken = createToken(tok);
        newToken->next = thead;
        thead = newToken;
        tok = strtok(NULL, delimiters);
    }

    free(copy);
    return thead;
}

void releaseTokens(token *t)
{
    if (t)
    {
        if (t->next)
            releaseTokens(t->next);
        if (t->token)
            free(t->token);
        free(t);
    }
}

int checkMetal(token *t, metal *m, quantity *q)
{
    token *tmp;
    char *startptr, *endptr, *metalString;
    float totalCost, cost;
    int units = 0;

    tmp = t->next;
    startptr = tmp->token;
    totalCost = strtof(startptr, &endptr);
    if (endptr == startptr || *endptr != '\0')
        return -1;
    while (tmp != NULL && strcmp(tmp->token, "is") != 0)
        tmp = tmp->next;
    if (tmp == NULL || tmp->next == NULL)
        return -1;
    tmp = tmp->next;
    metalString = tmp->token;
    tmp = tmp->next;
    while (tmp != NULL)
    {
        units += findQuantity(q, tmp->token);
        tmp = tmp->next;
    }
    if (units <= 0)
    {
        printf("No units found\n");
        return -1;
    }
    cost = totalCost / units;
    addMetal(&m, metalString, cost);
    printMetalList(m);

    return 0;
}

int main()
{
    char str[80];
    quantity *qhead = NULL;
    metal *mhead = NULL;
    token *t = NULL;
    int q = 0;

    puts("Enter the input (BLANK to quit):");
    while (1)
    {
        fgets(str, sizeof(str), stdin);
        str[strcspn(str, "\n")] = '\0';
        t = tokenizer(str);
        if (t == NULL)
            break;
        char *s = t->token;
        q = convertRomanNumber(s);
        if (q > 0)
            addQuantity(&qhead, t->next->next->token, q);
        else if (strcmp(s, "credits") == 0)
            checkMetal(t, mhead, qhead);
        else
            printf("I don't know\n");

        releaseTokens(t);
    }

    if (qhead != NULL)
        releaseQuantity(qhead);
    if (mhead != NULL)
        releaseMetal(mhead);

    return 0;
}

void printQuantityList(quantity *q)
{
    if (q)
    {
        if (q->next)
            printQuantityList(q->next);
        printf("%s\t=>\tQuantity: %d\n", q->quantity, q->unit);
    }
}

void printMetalList(metal *m)
{
    if (m)
    {
        if (m->next)
            printMetalList(m->next);
        printf("Metal %s, Cost: %.2f\n", m->metal, m->cost);
    }
}

void printTokenList(token *t)
{
    if (t)
    {
        if (t->next)
            printTokenList(t->next);
        printf("[ %s ]\n", t->token);
    }
}