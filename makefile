CC = gcc
CFLAGS = -I$(IDIR) -lmenu -lncurses
CFLAGSMEM = -g -O0 -I$(IDIR) -lmenu -lncurses

IDIR = ./include/
SRCDIR = ./src/

SOURCES = $(SRCDIR)*.c\
		  $(SRCDIR)utils/*.c\
		  $(SRCDIR)entities/*.c\
		  $(SRCDIR)entities/items/*.c\
		  $(SRCDIR)windows/*.c

all: clean rogue

rogue: $(SOURCES)
	$(CC) $(SOURCES) $(CFLAGS) -o $@

rogueMem: $(SOURCES)
	$(CC) $(SOURCES) $(CFLAGSMEM) -o rogue

run:
	./rogue

mem: clean rogueMem
	valgrind --leak-check=yes --log-file="log.txt" ./rogue

clean:
	@[ -f ./rogue ] && rm rogue || true