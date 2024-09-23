CC = gcc
CFLAGS = -lncurses -I$(IDIR)

IDIR = ./include/
SRCDIR = ./src/

SOURCES = $(SRCDIR)*.c

all: clean rogue

rogue:
	$(CC) $(SOURCES) $(CFLAGS) -o $@

run:
	./rogue

clean:
	@[ -f ./rogue ] && rm rogue || true