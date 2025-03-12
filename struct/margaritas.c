#include <stdio.h>

typedef union
{
    float lemon;
    int lime_pieces;
} lemon_lime;

typedef struct
{
    float tequila;
    float cointreau;
    lemon_lime citrus;
} margarita;

int main()
{
    margarita m = {2.0, 1.0, {2}};
    printf("%2.1f measures of tequila\n%2.1f measures of cointreau\n%2.1f measures of juice\n\n",
           m.tequila, m.cointreau, m.citrus.lemon);

    margarita f = {2.0, 1.0, {0.5}};
    printf("%2.1f measures of tequila\n%2.1f measures of cointreau\n%2.1f measures of juice\n\n",
           f.tequila, f.cointreau, f.citrus.lemon);

    margarita g = {2.0, 1.0, {.lime_pieces = 1}};
    printf("%2.1f measures of tequila\n%2.1f measures of cointreau\n%2.1f measures of juice\n\n",
           g.tequila, g.cointreau, g.citrus.lemon);

    return 0;
}