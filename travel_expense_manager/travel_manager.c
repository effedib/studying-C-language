#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define EPSILON 0.00001

#define NUM_CATEGORIES 3
#define MAX_LENGTH 80

int setup(short *daysOfTravel, float *initialBudget, char categories[NUM_CATEGORIES][MAX_LENGTH])
{
    puts("Enter the number of travel: ");
    scanf("%hi", daysOfTravel);
    getchar();
    puts("Enter the total budget: ");
    scanf("%f%*c", initialBudget);

    printf("Enter %i categories:\n", NUM_CATEGORIES);
    for (int i = 0; i < NUM_CATEGORIES; i++)
    {
        fgets(categories[i], MAX_LENGTH, stdin);
        categories[i][strcspn(categories[i], "\n")] = '\0';
        categories[i][0] = toupper((unsigned char)categories[i][0]);
    }

    return 0;
}

int calculateExpenses(float expenses[][NUM_CATEGORIES], char categories[NUM_CATEGORIES][MAX_LENGTH],
                      short *daysOfTravel)
{
    float expense;
    char input[MAX_LENGTH] = {'\0'};

    for (short day = 0; day < daysOfTravel[0]; day++)
    {
        printf("Day %d:\n", day + 1);
        for (short i = 0; i < NUM_CATEGORIES; i++)
        {
            printf("Enter the expenses for the category %s (ENTER to skip to next category)\n", categories[i]);
            expenses[day][i] = 0.0;
            expense = 0.0;
            while (1)
            {
                fgets(input, MAX_LENGTH, stdin);

                input[strcspn(input, "\n")] = '\0';
                if (strcmp(input, "") == 0)
                    break;

                // same result, but requires inverted execution order
                // if (strcmp(&input[0], "\n") == 0)
                //     break;
                // input[strcspn(input, "\n")] = '\0';

                if (sscanf(input, "%f", &expense) == 1)
                    expenses[day][i] += expense;
                else
                    puts("Invalid input. Please enter a valid number or 'ENTER'.\n");
            }
        }
    }

    return 0;
}

float sumExpenses(float totals[NUM_CATEGORIES], float expenses[][NUM_CATEGORIES], short *daysOfTravel)
{
    float granTotal = 0.0;
    for (short i = 0; i < NUM_CATEGORIES; i++)
    {
        for (short day = 0; day < daysOfTravel[0]; day++)
        {
            totals[i] += expenses[day][i];
            granTotal += expenses[day][i];
        }
    }

    return granTotal;
}

/**********************************************************************
void capitalizeCategories(char categories[NUM_CATEGORIES][MAX_LENGTH])
{
    while (*categories[0] != '\0')
    {
        **categories = toupper((unsigned char)**categories);
        categories++;
    }
}
***********************************************************************/

void displayTravelData(short *daysOfTravel, float *initialBudget, char categories[NUM_CATEGORIES][MAX_LENGTH],
                       float totals[NUM_CATEGORIES], float *granTotal, float *residualBudget)
{
    printf("Days of travel: %hi\n\n", *daysOfTravel);
    printf("Initial budget: %.2f\n\n", *initialBudget);
    for (int i = 0; i < NUM_CATEGORIES; i++)
    {
        printf("Category %s\nTotal Expenses: %.2f\n\n", categories[i], totals[i]);
    }
    printf("Gran Total: %.2f\n\n", *granTotal);

    if (*residualBudget < -EPSILON)
        printf("Budget exceeded, residual %.2f\n", *residualBudget);
    else if (*residualBudget > EPSILON)
        printf("Residul budget: %.2f\n", *residualBudget);
    else
        printf("Budget perfectly respected!\n");
}

int main()
{
    short daysOfTravel = 0;
    float initialBudget = 0.0;
    char categories[NUM_CATEGORIES][MAX_LENGTH];

    setup(&daysOfTravel, &initialBudget, categories);
    // capitalizeCategories(categories);

    float expenses[daysOfTravel][NUM_CATEGORIES];
    calculateExpenses(expenses, categories, &daysOfTravel);

    float totals[NUM_CATEGORIES] = {0.0};
    float granTotal = sumExpenses(totals, expenses, &daysOfTravel);

    float residualBudget = initialBudget - granTotal;

    displayTravelData(&daysOfTravel, &initialBudget, categories, totals, &granTotal, &residualBudget);

    return 0;
}