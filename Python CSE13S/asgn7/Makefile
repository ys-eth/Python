CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic -g 
DEPEND = identify.o pq.o text.o parser.o bf.o bv.o ht.o node.o speck.o
CHECK = --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose

LFLAGS = $(shell pkg-config --libs gmp) -lm

# <target name>: <target dependencies>
# <TAB> command

.PHONY: all scan-build valgrind

all: identify

test: $(DEPEND)
	$(CC) $(LFLAGS) -o test $(DEPEND)

test.o: test.c
	$(CC) $(CFLAGS) -c test.c

identify: $(DEPEND)
	$(CC) -o identify $(DEPEND) -lm

identify.o: identify.c
	$(CC) $(CFLAGS) -c identify.c

texts: $(DEPEND)
	$(CC) -o texts $(DEPEND)

text.o: text.c
	$(CC) $(CFLAGS) -c text.c

bf.o: bf.c
	$(CC) $(CFLAGS) -c bf.c

bv.o: bv.c
	$(CC) $(CFLAGS) -c bv.c

ht.o: ht.c
	$(CC) $(CFLAGS) -c ht.c

node.o: node.c
	$(CC) $(CFLAGS) -c node.c

parser.o: parser.c
	$(CC) $(CFLAGS) -c parser.c

pq.o: pq.c
	$(CC) $(CFLAGS) -c pq.c

speck.o: speck.c
	$(CC) $(CFLAGS) -c speck.c

clean:
	rm -f identify.o identify text.o bf.o bv.o ht.o node.o parser.o pq.o speck.o

scan-build: clean	
	scan-build --use-cc=$(CC) make

valgrind: test 
	valgrind $(CHECK) ./identify

format:
	clang-format -i -style=file *.[ch]

