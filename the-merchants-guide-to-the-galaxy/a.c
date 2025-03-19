#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include "convertRomanNumber.h"

typedef struct quantity
{
    char *quantity;
    char *romanUnit;
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

typedef struct splitted
{
    char *prefix;
    char *suffix;
} splitted;

void printQuantityList(quantity *q);
void printMetalList(metal *m);
void printTokenList(token *t);

quantity *createQuantity(quantity **head, char *inputStr, char *inputUnit)
{
    quantity *i = malloc(sizeof(quantity));
    i->quantity = strdup(inputStr);
    i->romanUnit = strdup(inputUnit);
    i->next = *head;
    *head = i;

    return i;
}

quantity *addQuantity(quantity **head, char *inputStr, char *inputUnit)
{
    quantity *tmp = *head;
    while (tmp != NULL)
    {
        if (strcmp(tmp->quantity, inputStr) == 0)
        {
            tmp->romanUnit = strdup(inputUnit);
            return tmp;
        }
        tmp = tmp->next;
    }
    return createQuantity(head, inputStr, inputUnit);
}

void releaseQuantity(quantity *q)
{
    if (q)
    {
        if (q->next)
            releaseQuantity(q->next);
        if (q->quantity)
            free(q->quantity);
        if (q->romanUnit)
            free(q->romanUnit);
        free(q);
    }
}

int sumQuantity(quantity *q, token *t)
{
    int length = 0;
    token *ttemp = t;
    quantity *qtemp = q;
    while (ttemp != NULL)
    {
        length++;
        ttemp = ttemp->next;
    }

    char *finalString = (char *)malloc((length + 1) * sizeof(char));
    if (finalString == NULL)
    {
        printf("Errore di allocazione della memoria\n");
        exit(1);
    }

    finalString[length--] = '\0';
    ttemp = t;
    while (ttemp != NULL)
    {
        while (qtemp != NULL)
        {
            if (strcmp(ttemp->token, qtemp->quantity) == 0)
            {
                finalString[length--] = *qtemp->romanUnit;
                break;
            }
            else
                qtemp = qtemp->next;
        }
        qtemp = q;
        ttemp = ttemp->next;
    }
    int num = convertRomanNumber(finalString);
    free(finalString);
    return num;
}

metal *createMetal(metal **head, char *stringMetal, float cost)
{
    metal *m = malloc(sizeof(metal));
    m->metal = strdup(stringMetal);
    m->cost = cost;
    m->next = *head;
    *head = m;

    return m;
}

metal *addMetal(metal **head, char *stringMetal, float cost)
{
    metal *tmp = *head;
    while (tmp != NULL)
    {
        if (strcmp(tmp->metal, stringMetal) == 0)
        {
            tmp->cost = cost;
            return tmp;
        }
        tmp = tmp->next;
    }
    return createMetal(head, stringMetal, cost);
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

void tokenizer(token **thead, char *string)
{
    char *tok, *copy;
    const char delimiters[] = " .,;:!-";

    copy = strdup(string);
    tok = strtok(copy, delimiters);
    while (tok != NULL)
    {
        token *newToken = createToken(tok);
        if (thead == NULL)
            *thead = newToken;
        else
        {
            newToken->next = *thead;
            *thead = newToken;
        }
        tok = strtok(NULL, delimiters);
    }
    free(copy);
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

int checkMetal(token *t, metal **m, quantity *q)
{
    token *tmp = t->next;
    char *startptr, *endptr, *metalString;
    float totalCost, cost;
    int units = 0;

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
    units = sumQuantity(q, tmp);
    if (units <= 0)
    {
        printf("No units found\n");
        return -1;
    }
    cost = totalCost / units;
    addMetal(m, metalString, cost);
    printMetalList(*m);

    return 0;
}

/* void matchPattern(const char *string, const char *pattern) {
    regex_t regex;
    int reti;

    // Compilare il pattern
    reti = regcomp(&regex, pattern, REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    // Eseguire la ricerca del pattern
    reti = regexec(&regex, string, 0, NULL, 0);
    if (!reti) {
        printf("Pattern found: %s\n", pattern);
    } else if (reti == REG_NOMATCH) {
        printf("Pattern not found: %s\n", pattern);
    } else {
        char msgbuf[100];
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        exit(1);
    }

    // Liberare la memoria allocata per il pattern
    regfree(&regex);
} */

int main()
{
    char str[80];
    quantity *qhead = NULL;
    metal *mhead = NULL;
    token *t = NULL;
    int q = 0, tokenListSize = 0;

    while (1)
    {
        puts("Enter the input (BLANK to quit):");
        fgets(str, sizeof(str), stdin);
        str[strcspn(str, "\n")] = '\0';
        tokenizer(&t, str);
        if (t == NULL)
            break;
        char *s = t->token;
        q = convertRomanNumber(s);
        if (q > 0)
            addQuantity(&qhead, t->next->next->token, s);
        else if (strcmp(s, "credits") == 0)
            checkMetal(t, &mhead, qhead);
        else
            printf("I don't know\n");

        releaseTokens(t);
        t = NULL;
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
        printf("%s\t=>\tQuantity: %d\n", q->quantity, convertRomanNumber(q->romanUnit));
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