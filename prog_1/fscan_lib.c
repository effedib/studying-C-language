#include <stdio.h>

int main(void)
{
  int codice;
  int quantita;
  int contatore=0;
  int esito;

  printf("Inserisci codice e quantita: ");
  while ((esito=fscanf(stdin, "%d %d", &codice, &quantita))==2) {
    printf("Codice: %d, Quantita: %d\n", codice, quantita);
    contatore++;
    printf("Inserisci codice e quantita: ");
  }

  if (ferror(stdin)) {
    puts("Errore di lettura\n");
    return 1;
  }

  if (esito==EOF) {
    printf("\nTotale coppie: %d\n", contatore);
    return 0;
  }

  puts("\nDati incompleti o non validi\n");

  return 1;
}
