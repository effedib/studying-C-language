#include <stdio.h>
#include <stdlib.h>

int leggiEAvanza(int **cursore, int *fine, int *letto) {
  if (*cursore==fine) {
    return 0;
  }

  *letto=*(*cursore++);
  return 1;
}

int main(void)
{
    int v[] = {6, 12, 18, 24};
    int *p = v;

    int a = (*p)++;
    int b = *++p;
    int c = *p++;

    ++*p;

    printf("%d %d %d\n", a, b, c);
    printf("%d %d %d %d\n", v[0], v[1], v[2], v[3]);
    printf("%d\n", *p);

    return 0;
}
