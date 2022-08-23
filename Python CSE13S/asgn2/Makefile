CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic


# <target name>: <target dependencies>
# <TAB> command


.PHONY: all 

all: integrate testfile

testfile: testfile.o mathlib.o 
	$(CC) -o testfile -lm testfile.o mathlib.o

mathlib.o: mathlib.c
	$(CC) $(CFLAGS) -c mathlib.c

testfile.o: testfile.c
	$(CC) $(CFLAGS) -c testfile.c 

integrate: integrate.o mathlib.o functions.o
	$(CC) -o integrate -lm integrate.o mathlib.o functions.o

functions.o: functions.c
	$(CC) $(CFLAGS) -c functions.c

integrate.o: integrate.c
	$(CC) $(CFLAGS) -c integrate.c

clean:
	rm -f mathlib mathlib.o integrate.o functions.o integrate testfile.o testfile

format: 
	clang-format -i -style=file *.[ch]
