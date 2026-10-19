CFLAGS = -std=c18 -Wall -Wextra -Wpedantic -Werror -g -fsanitize=address,undefined -fno-omit-frame-pointer

.PHONY: all run clean

all: run

serie.o: serie.h serie.c
	gcc $(CFLAGS) -c serie.c -o serie.o

esercizi.o: serie.h esercizi.c
	gcc $(CFLAGS) -c esercizi.c -o esercizi.o

a.out: serie.o esercizi.o
	gcc $(CFLAGS) esercizi.o serie.o -o a.out

run: a.out
	./a.out

clean:
	rm -f *.out *.o
