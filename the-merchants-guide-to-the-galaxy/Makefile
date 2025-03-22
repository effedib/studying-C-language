all: merchants

convertRomanNumber.o: convertRomanNumber.c convertRomanNumber.h
	gcc -c convertRomanNumber.c

merchants: merchants.c convertRomanNumber.o
	gcc -g merchants.c convertRomanNumber.o -o merchants.out

clean:
	rm *.out
	rm *.o