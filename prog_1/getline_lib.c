#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>

int main(void) {
  char *riga = NULL;
  size_t capacita = 0;

  ssize_t letti=0;
  ssize_t max=-1;
  int contatore = 0;
  int contatore_max = 0;
while ((letti = getline(&riga, &capacita, stdin)) >= 0) {
    contatore++;
    if (letti > 0 && riga[letti - 1] == '\n') {
      letti--;
    }

    if (letti > max) {
      max = letti;
      contatore_max = contatore;
    }
  }

  if (ferror(stdin)) {
    puts("Errore di lettura");
    free(riga);
    return 1;
  }

  if (max >= 0) {
    printf("Riga: %d\tByte letti: %zd\n", contatore_max, max);
  } else {
    puts("Nessuna riga");
  }

  free(riga);
  return 0;
}
