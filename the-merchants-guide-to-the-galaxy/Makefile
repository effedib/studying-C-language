all: a

convertRomanNumber.o: convertRomanNumber.c convertRomanNumber.h
	gcc -c convertRomanNumber.c

a: a.c convertRomanNumber.o
	gcc -g a.c convertRomanNumber.o -o a.out

clean:
	rm *.out
	rm *.o