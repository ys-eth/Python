CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic
DEPEND = sorting.o insert.o stats.o quick.o batcher.o heap.o
CHECK = --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose

# <target name>: <target dependencies>
# <TAB> command

.PHONY: all scan-build valgrind

all: sorting

sorting: $(DEPEND) 
	$(CC) -o sorting $(DEPEND)

sorting.o: sorting.c
	$(CC) $(CFLAGS) -c sorting.c

insert.o: insert.c
	$(CC) $(CFLAGS) -c insert.c

stats.o: stats.c
	$(CC) $(CFLAGS) -c stats.c

quick.o: quick.c
	$(CC) $(CFLAGS) -c quick.c	

batcher.o: batcher.c
	$(CC) $(CFLAGS) -c batcher.c

heap.o: heap.c
	$(CC) $(CFLAGS) -c heap.c

clean:
	rm -f sorting.o sorting heap.o insert.o quick.o batcher.o stats.o

scan-build: clean
	scan-build --use-cc=$(CC) make

valgrind: sorting
	valgrind $(CHECK) ./sorting -a -n 96 -p 0

format:
	clang-format -i -style=file *.[ch]
