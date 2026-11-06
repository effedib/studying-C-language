#include <stdio.h>
#include <stdlib.h>
#include "serie.h"

int main(void)
{
  int dati[4] = {-5,18,27,60};

  struct Serie originale = {42,dati,4};
  struct Serie duplicata = {0,NULL,0};

  int ris = duplicaSerie(&originale, &duplicata);
  if (ris) {
    duplicata.letture[0] = 99;
    printf("\nOriginale\n");
    stampaSerie(&originale);
    printf("\nDuplicata\n");
    stampaSerie(&duplicata);
  }

  free(duplicata.letture);
  duplicata.letture=NULL;

  return 0;
}
