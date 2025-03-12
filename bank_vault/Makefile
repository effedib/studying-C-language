all: encrypt.o checksum.o libhfsecurity.a bank_vault

encrypt.o: encrypt.c
	gcc -c encrypt.c -I../my_header_files -o out/encrypt.o

checksum.o: checksum.c
	gcc -c checksum.c -I../my_header_files -o out/checksum.o

libhfsecurity.a: out/encrypt.o out/checksum.o
	ar -rcs ../my_lib/libhfsecurity.a out/encrypt.o out/checksum.o

bank_vault: bank_vault.c
	gcc bank_vault.c -I../my_header_files -L../my_lib -lhfsecurity -o bank_vault


clean:
	rm ./bank_vault
	rm *.a
	rm *.o