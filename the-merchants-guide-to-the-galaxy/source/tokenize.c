#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <tokenize.h>

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
