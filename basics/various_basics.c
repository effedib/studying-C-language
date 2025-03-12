#include <stdio.h>
#include <string.h>

void print_reverse(char *s)
{
    size_t len = strlen(s);
    char *t = s + len - 1;
    while (t >= s)
    {
        printf("%c", *t);
        t = t - 1;
    }
    puts("");
}

void search_for()
{
    char search_for[80];
    printf("Search for: ");
    fgets(search_for, 80, stdin);
    search_for[strlen(search_for) - 1] = '\0';
}

int main()
{
    printf("int: %i\n", (int)sizeof(int));
    printf("short: %hi\n", (short)sizeof(short));
    printf("long: %li\n", sizeof(long));

    unsigned int x = 7;
    int y = 2;
    float z = (float)x / y;
    printf("z = %.2f\n", z);

    return 0;
}