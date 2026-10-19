#include <stdio.h>

int creaEtichetta(char *uscita, int capacita, int codice, int quantita) {
  if (
    uscita==NULL
    || capacita<=0
    || codice<1
    || codice>999
    || quantita<0
    || quantita>100
  ) {
    return -1;
  }

  int n = snprintf(uscita, capacita, "P%d-Q%d", codice, quantita);

  if (n<0) return -1;
  else if (n>=capacita) return 0;
  else return 1;
}

void stampaEtichetta(char *uscita, int capacita, int codice, int quantita) {
  int esito = creaEtichetta(uscita, capacita, codice, quantita);
  if (esito!=-1) printf("Esito: %d Testo: [%s]\n", esito, uscita);
}


int main(void) {
  char buf1[9]; char buf2[8]; char buf3[1];

  int cod=125; int quantity=38;

  stampaEtichetta(buf1, sizeof buf1, cod, quantity);
  stampaEtichetta(buf2, sizeof buf2, cod, quantity);
  stampaEtichetta(buf3, sizeof buf3, cod, quantity);

  return 0;
}
