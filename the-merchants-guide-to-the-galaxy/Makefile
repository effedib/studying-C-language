all: convertRomanNumber.o tokenize.o quantity.o metal.o libimports.a merchants

convertRomanNumber.o: ./source/convertRomanNumber.c
	gcc -I./includes -fPIC -c ./source/convertRomanNumber.c -o ./objects/convertRomanNumber.o

tokenize.o: ./source/tokenize.c
	gcc -I./includes -fPIC -c ./source/tokenize.c -o ./objects/tokenize.o

quantity.o: ./source/quantity.c
	gcc -I./includes -fPIC -c ./source/quantity.c -o ./objects/quantity.o

metal.o: ./source/metal.c
	gcc -I./includes -fPIC -c ./source/metal.c -o ./objects/metal.o

libimports.a: convertRomanNumber.o tokenize.o quantity.o metal.o
	ar -rcs ./mylib/libimports.a ./objects/convertRomanNumber.o ./objects/tokenize.o ./objects/quantity.o ./objects/metal.o

merchants: merchants.c
	gcc -g merchants.c -I./includes -fPIC -L./mylib -limports -o merchants.out

clean:
	rm *.out
	rm *.o