CC = gcc
CFLAGS = -ansi -Wall -pedantic
DEPS = permut.h
OBJ = permut.o

%.o:  %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

permut: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
