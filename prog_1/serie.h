#ifndef SERIE_H
#define SERIE_H

struct Serie {
  int codice;
  int *letture;
  int n;
};

int duplicaSerie(const struct Serie *origine, struct Serie *uscita);
void stampaSerie(const struct Serie *serie);

#endif
