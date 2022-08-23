CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic
DEPEND = universe.o life.o
CHECK = --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose

LFLAGS = $(shell pkg-config --libs ncurses)

# <target name>: <target dependencies>
# <TAB> command

.PHONY: all scan-build valgrind

all: life

life: $(DEPEND)
	$(CC) $(LFLAGS) -o life $(DEPEND)

life.o: life.c
	$(CC) $(CFLAGS) -c life.c

test: universe.o test.o
	$(CC) -o test universe.o test.o

test.o: test.c
	$(CC) $(CFLAGS) -c test.c

universe.o: universe.c
	$(CC) $(CFLAGS) -c universe.c

clean:
	rm -f life.o life universe.o

scan-build: clean
	scan-build --use-cc=$(CC) make

valgrind: life
	valgrind $(CHECK) ./life -i lines.txt -n 10

format:
	clang-format -i -style=file *.[ch]
