#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <regex.h>
#include <convertRomanNumber.h>
#include <quantity.h>
#include <metal.h>
#include <tokenize.h>

int sumQuantity(quantity *q, tokenArray *t)
{
    /**
     * Sums the quantities represented by Roman numerals in the token array.
     *
     * @param q Pointer to the head of the quantity linked list.
     * @param t Pointer to the token array containing the quantities.
     * @return The sum of the quantities as an integer.
     */

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
    /**
     * Checks the metal and calculates its cost per unit.
     *
     * @param prefix Pointer to the token array containing the prefix.
     * @param suffix Pointer to the token array containing the suffix.
     * @param m Pointer to the head of the metal linked list.
     * @param q Pointer to the head of the quantity linked list.
     * @return Pointer to the new metal structure with updated cost per unit.
     */

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
    /**
     * Calculates the total credits for a given metal based on its quantity.
     *
     * @param t Pointer to the token array containing the metal and quantity.
     * @param mhead Pointer to the head of the metal linked list.
     * @param qhead Pointer to the head of the quantity linked list.
     * @return The total credits as a float.
     */

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
    /**
     * Matches a string against a given regular expression pattern.
     *
     * @param string The string to be matched.
     * @param pattern The regular expression pattern.
     * @return 0 if the pattern matches, otherwise a non-zero value.
     */

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