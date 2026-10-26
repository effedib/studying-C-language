#include <stdio.h>

int main(void)
{
  int v[] = {4, 8, 12};
  int *p = v;

  int a = *p++;
  int b = ++*p;
  int c = (*p)++;

  printf("a: %d\n", a);
  printf("b: %d\n", b);
  printf("c: %d\n", c);

  for (int i=0; i<3; i++) {
    printf("%d ", v[i]);
  }
  printf("\n");

  return 0;
}
