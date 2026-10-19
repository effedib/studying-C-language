#include <stdio.h>
#include <string.h>

int controllaInput(char *buffer, size_t *index) {
  *index = strcspn(buffer, "\n");
  if (buffer[*index]=='\n') {
    buffer[*index]='\0';
    return 1;
  }

  return 0;
}

int memorizzaInput(char *buffer, int capacita, size_t *lunghezza) {
  if (fgets(buffer, capacita, stdin)==NULL) {
    printf("Acquisizione incompleta\n");
    return -1;
  }

  if (!controllaInput(buffer, lunghezza)) {
    int c;
    if ((c=getchar())=='\n' || c==EOF) {
      return 1;
    }

    while ((c=getchar())!='\n' && c!=EOF) {}

    return 0;
  }

  return 1;
}

int main(void)
{
  char buffer[9];
  size_t lunghezza;

  for (int i=0; i<2; i++) {
    int esito;
    while ((esito=memorizzaInput(buffer, sizeof buffer, &lunghezza))!=1) {
      if (esito==0) printf("Riga troppo lunga\n");
      else return 1;
    }
    printf("Riga: %d, testo: [%s], lunghezza: %zu\n", i+1, buffer, lunghezza);
  }

  return 0;
}
