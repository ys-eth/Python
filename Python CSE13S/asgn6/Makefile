CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic -g
DEPEND = node.o pq.o code.o stack.o io.o huffman.o test.o 
DEPEND1 = node.o pq.o code.o stack.o io.o huffman.o encode.o 
DEPEND2 = node.o pq.o code.o stack.o io.o huffman.o decode.o
CHECK = --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose

LFLAGS = $(shell pkg-config --libs gmp) -lm

# <target name>: <target dependencies>
# <TAB> command

.PHONY: all scan-build valgrind

all: encode decode

test: $(DEPEND)
	$(CC) $(LFLAGS) -o test $(DEPEND)

test.o: test.c
	$(CC) $(CFLAGS) -c test.c

encode: $(DEPEND1)
	$(CC) -o encode $(DEPEND1)

encode.o: encode.c
	$(CC) $(CFLAGS) -c encode.c

decode: $(DEPEND2)
	$(CC) -o decode $(DEPEND2)

decode.o: decode.c
	$(CC) $(CFLAGS) -c decode.c

node.o: node.c
	$(CC) $(CFLAGS) -c node.c

pq.o: pq.c
	$(CC) $(CFLAGS) -c pq.c

code.o: code.c
	$(CC) $(CFLAGS) -c code.c

io.o: io.c
	$(CC) $(CFLAGS) -c io.c

stack.o: stack.c
	$(CC) $(CFLAGS) -c stack.c

huffman.o: huffman.c
	$(CC) $(CFLAGS) -c huffman.c

clean:
	rm -f encode.o encode decode.o decode node.o pq.o code.o io.o stack.o huffman.o

scan-build: clean	
	scan-build --use-cc=$(CC) make

valgrind: encode decode
	valgrind $(CHECK) ./encode ./decode 

format:
	clang-format -i -style=file *.[ch]

