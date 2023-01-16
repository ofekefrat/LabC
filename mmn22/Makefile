CC = gcc
CFLAGS = -ansi -Wall -pedantic
DEPS = set.h
OBJ = myset.o set.o

%.o:  %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

myset: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
