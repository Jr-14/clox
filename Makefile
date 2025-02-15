CC = gcc
SRCDIR = src
BINDIR = bin
CFLAGS = -I$(SRCDIR) -Wall
DEPS = $(SRCDIR)/common.h $(SRCDIR)/chunk.h
OBJ = $(BINDIR)/main.o

$(BINDIR)/%.o: $(SRCDIR)/%.c $(DEPS)
	@mkdir -p $(BINDIR)
	$(CC) -c -o $@ $< $(CFLAGS)

$(BINDIR)/main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean run
clean:
	rm -rf $(BINDIR)

run:
	./$(BINDIR)/main
