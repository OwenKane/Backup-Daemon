CC=gcc
objects = main.o timer.o locked.o log.o find_updated.o 
headers = main.h timer.h locked.h log.h find_updated.h 

myprog : $(objects)
	$(CC) -o prog $(objects) -lm

main.o : main.c $(headers)
	$(CC) -c main.c
	
timer.o : timer.c
	$(CC) -c timer.c

locked.o : locked.c
	$(CC) -c locked.c

log.o : log.c
	$(CC) -c log.c

find_updated.o : find_updated.c
	$(CC) -c find_updated.c

clean: 
	rm prog main.o timer.o locked.o log.o find_updated.o

