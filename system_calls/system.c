#include <stdlib.h>
#include <stdio.h>
#include <time.h>

char *now()
{
    time_t t;
    time(&t);
    return asctime(localtime(&t));
}

int main()
{
    char comment[80];
    char cmd[120];

    fgets(comment, 80, stdin);
    sprintf(cmd, "echo '%s %s' >> ./IO/reports.log", comment, now());
    printf("USER=>%s\n", getenv("USER"));

    system(cmd);

    return 0;
}