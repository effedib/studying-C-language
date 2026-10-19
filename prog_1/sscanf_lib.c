#include <stdio.h>
#include <string.h>

int memorizzaInput(char *buffer, int capacita) {
  if (fgets(buffer, capacita, stdin)==NULL) {
    printf("Lettura non riuscita\n");

    return 0;
  }

  size_t index = strcspn(buffer, "\n");
  if (buffer[index]=='\n') {
    buffer[index]='\0';
  } else {
    int c;
    while ((c=getchar())!='\n' && c!=EOF) {}
  }

  return 1;
}

int main(void) {
  int codice;
  int quantita;
  char extra;

  char buf[64];

  if (!memorizzaInput(buf, sizeof buf)) {
    return 1;
  }

  int letti = sscanf(buf, "%d %d %c", &codice, &quantita, &extra);
  if (
    letti!=2
    || codice<1
    || codice>999
    || quantita<0
    || quantita>100
  ) {
    printf("Dati non validi\n");

    return 1;
  }

  printf("Codice: %d, Quantita: %d\n", codice, quantita);

  return 0;
}
