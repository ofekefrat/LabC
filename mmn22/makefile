CFLAGS = -ansi -wall -pedantic

myset: myset.o set.o
	gcc $(CFLAGS) myset.o -o myset

myset.o: myset.c set.h
	gcc $(CFLAGS) -c myset.c

set.o: set.c set.h
	gcc $(CFLAGS) -c set.c