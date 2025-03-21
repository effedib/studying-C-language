all: merchants

convertRomanNumber.o: convertRomanNumber.c convertRomanNumber.h
	gcc -c convertRomanNumber.c

a: a.c convertRomanNumber.o
	gcc -g a.c convertRomanNumber.o -o a.out

merchants: merchants.c convertRomanNumber.o
	gcc -g merchants.c convertRomanNumber.o -o merchants.out

clean:
	rm *.out
	rm *.o