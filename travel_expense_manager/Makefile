PROGNAME=travel_manager

all: travel_manager

travel_manager.o: travel_manager.c
	gcc -c travel_manager.c

travel_manager: travel_manager.c
	gcc travel_manager.c -o travel_manager

clean:
	rm -f *.o