CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic -g
DEPED = randstate.o rsa.o numtheory.o encrypt.o
DEPEND = randstate.o numtheory.o rsa.o keygen.o
DEPEND1 = randstate.o numtheory.o rsa.o test.o
DEPEND2 = randstate.o rsa.o numtheory.o decrypt.o
CHECK = --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose

LFLAGS = $(shell pkg-config --libs gmp) -lm

# <target name>: <target dependencies>
# <TAB> command

.PHONY: all scan-build valgrind

all: keygen encrypt decrypt

test: $(DEPEND1)
	$(CC) $(LFLAGS) -o test $(DEPEND1)

test.o: test.c
	$(CC) $(CFLAGS) -c test.c

encrypt: $(DEPED)
	$(CC) $(LFLAGS) -o encrypt $(DEPED)

encrypt.o: encrypt.c
	$(CC) $(CFLAGS) -c encrypt.c

decrypt: $(DEPEND2)
	$(CC) $(LFLAGS) -o decrypt $(DEPEND2)

decrypt.o: decrypt.c
	$(CC) $(CFLAGS) -c decrypt.c

keygen: $(DEPEND)
	$(CC) $(LFLAGS) -o keygen $(DEPEND)

keygen.o: keygen.c
	$(CC) $(CFLAGS) -c keygen.c

randstate.o: randstate.c
	$(CC) $(CFLAGS) -c randstate.c

numtheory.o: numtheory.c
	$(CC) $(CFLAGS) -c numtheory.c

rsa.o: rsa.c
	$(CC) $(CFLAGS) -c rsa.c

clean:
	rm -f keygen.o keygen encrypt.o encrypt decrypt.o decrypt randstate.o numtheory.o rsa.o 

scan-build: clean
	scan-build --use-cc=$(CC) make

valgrind: decrypt
	valgrind $(CHECK) ./decrypt -i output.txt -o final.txt	

format:
	clang-format -i -style=file *.[ch]
