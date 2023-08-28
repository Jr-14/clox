CC=gcc
CFLAGS=-I. -Wall
DEPS = chunk.h common.h memory.h debug.h
OBJ = main.o chunk.o memory.o debug.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)