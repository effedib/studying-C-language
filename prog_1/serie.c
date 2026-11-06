#include <stdio.h>
#include <stdlib.h>
#include "serie.h"

int duplicaSerie(const struct Serie *origine, struct Serie *uscita) {
  if (
    origine==NULL
    || uscita==NULL
    || origine==uscita
    || origine->n<0
    || (origine->n==0 && origine->letture!=NULL)
    || (origine->n>0 && origine->letture==NULL)
    || uscita->letture!=NULL
    || uscita->n!=0
  ) {
    return 0;
  }

  if (origine->n==0 || origine->letture==NULL) {
    uscita->n=origine->n;
    uscita->codice=origine->codice;
    uscita->letture=NULL;
    return 1;
  }

  int *p = malloc(origine->n * sizeof *p);
  if (p==NULL) {
    return 0;
  }

  uscita->n=origine->n;
  uscita->codice=origine->codice;
  uscita->letture=p;
  for (int i=0; i<origine->n; i++) {
    uscita->letture[i]=origine->letture[i];
  }

  return 1;
}

void stampaSerie(const struct Serie *serie) {
  printf("codice: %d\n", serie->codice);
  printf("dimensione: %d\n", serie->n);
  for (int i=0; i<serie->n; i++) {
    printf("lettura %d: %d\n", i, serie->letture[i]);
  }
}
