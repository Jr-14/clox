CC = gcc
SRCDIR = src
BINDIR = bin
CFLAGS = -I$(SRCDIR) -Wall
SRC = $(wildcard $(SRCDIR)/*.c)
OBJ = $(patsubst $(SRCDIR)/%.c, $(BINDIR)/%.o, $(SRC))

$(BINDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(BINDIR)
	$(CC) -c -o $@ $< $(CFLAGS)

$(BINDIR)/main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean run
clean:
	rm -rf $(BINDIR)

run:
	./$(BINDIR)/main
