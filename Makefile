CC=gcc
CFLAGS=-I. -Wall
DEPS = chunk.h common.h memory.h debug.h value.h vm.h
OBJ = main.o chunk.o memory.o debug.o value.o vm.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)