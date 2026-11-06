#include <stdio.h>
#include <stdlib.h>

struct Serie {
  int codice;
  int *letture;
  int n;
};

int duplicaSerie(const struct Serie *origine, struct Serie *uscita) {
  if (
    origine==NULL
    || uscita==NULL
    || origine==uscita
    || origine->n<0
    || (origine->n==0 && origine->letture!=NULL)
    || (origine->n>0 && origine->letture==NULL)
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
  printf("\ncodice: %d\n", serie->codice);
  printf("dimensione: %d\n", serie->n);
  for (int i=0; i<serie->n; i++) {
    printf("lettura %d: %d\n", i, serie->letture[i]);
  }
}


int main(void)
{
  int dati[4] = {-5,18,27,60};

  struct Serie originale = {42,dati,4};
  struct Serie duplicata = {0,NULL,0};

  int ris = duplicaSerie(&originale, &duplicata);
  if (ris) {
    duplicata.letture[0] = 99;
    printf("Originale\n");
    stampaSerie(&originale);
    printf("Duplicata\n");
    stampaSerie(&duplicata);
  }

  free(duplicata.letture);
  duplicata.letture=NULL;

  return 0;
}
