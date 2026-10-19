#include <stdio.h>

int main(void)
{
  int v[] = {2,4,6,8};
  // int *p = v+4;

  for (int *p=v+4; p>=v; --p) {
    printf("%d ", *p);
  }
  printf("\n");

  return 0;
}
