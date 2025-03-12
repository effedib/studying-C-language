all: hfcal.o elliptical.o libhfcal.a elliptical

hfcal.o: hfcal.c
	gcc -I./includes -fPIC -c hfcal.c -o hfcal.o

elliptical.o: elliptical.c
	gcc -I./includes -fPIC -c elliptical.c -o elliptical.o

libhfcal.a: hfcal.o
	ar -rcs ./libs/libhfcal.a hfcal.o

elliptical: elliptical.o
	gcc elliptical.o -L./libs -lhfcal -o elliptical
