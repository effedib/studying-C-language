#include <stdio.h>
#include <string.h>

int main(void)
{
  char riga[32];
  int counter_empty=0;
  int counter_non_empty=0;

  while (fgets(riga, sizeof riga, stdin)!=NULL) {
    size_t index = strcspn(riga, "\n");
    if (riga[index]=='\n') {
      riga[index]='\0';
    }

    size_t length = strlen(riga);
    if (length>0) counter_non_empty++;
    else counter_empty++;
  }

  if (ferror(stdin)) {
    printf("Errore di lettura\n");

    return 1;
  }

  printf("\nRighe non vuote: %d", counter_non_empty);
  printf("\nRighe vuote: %d\n", counter_empty);

  return 0;
}
