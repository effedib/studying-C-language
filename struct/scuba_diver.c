#include <stdio.h>

typedef struct
{
    float tank_capacity;
    int tank_psi;
    const char *suit_material;
} equipment;

typedef struct
{
    int age[2];
} anagraph;

typedef struct scuba
{
    const char *name;
    equipment kit;
    anagraph detail;
} diver;

void badge(diver d)
{
    printf("Name: %s Tank: %2.2f(%i) Suit: %s\n",
           d.name, d.kit.tank_capacity, d.kit.tank_psi, d.kit.suit_material);
}

void incrementAge(diver *d)
{
    (*d).detail.age[1]++;
    printf("Age updated: %i\n", (*d).detail.age[1]);
}

int main()
{
    diver randy = {"Randy", {5.5, 3500, "Neoprene"}, {{10, 20}}};
    badge(randy);
    incrementAge(&randy);
    printf("Age returned: %i\n", randy.detail.age[1]);

    return 0;
}
