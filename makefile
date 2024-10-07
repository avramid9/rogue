CC = gcc
CFLAGS = -g -O0 -lncurses -I$(IDIR)

IDIR = ./include/
SRCDIR = ./src/

SOURCES = $(SRCDIR)*.c\
		  $(SRCDIR)utils/*.c

all: clean rogue

rogue: $(SOURCES)
	$(CC) $(SOURCES) $(CFLAGS) -o $@

run:
	./rogue

mem:
	valgrind --leak-check=yes --log-file="log.txt" ./rogue

clean:
	@[ -f ./rogue ] && rm rogue || true