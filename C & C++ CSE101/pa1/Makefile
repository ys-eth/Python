# /****************************************************************************************
# *  Name: Yash Sharma
# *  Cruz ID: yhsharma
# *  Assignment Name: pa1
# *****************************************************************************************/

#------------------------------------------------------------------------------
# Makefile for CSE 101 Programming Assignment 1
#
# make                   makes Lex
# make ListClient        makes ListClient
# make clean             removes all binaries
# make checkClient       checks ListClient for memory errors
# make checkLex          checks Lex for memory errors
#------------------------------------------------------------------------------

Lex: Lex.o List.o
	gcc -std=c17 -Wall -g -o Lex Lex.o List.o

Lex.o: Lex.c List.h
	gcc -std=c17 -Wall -g -c Lex.c

ListClient: ListClient.o List.o
	gcc -std=c17 -Wall -g -o ListClient ListClient.o List.o

ListClient.o: ListClient.c List.h
	gcc -std=c17 -Wall -g -c ListClient.c

ListTest: ListTest.o List.o
	gcc -std=c17 -Wall -g -o ListTest ListTest.o List.o

ListTest.o: ListTest.c List.h
	gcc -std=c17 -Wall -g -c ListTest.c

List.o: List.c List.h
	gcc -std=c17 -Wall -g -c List.c

clean:
	rm -f ListTest ListTest.o Lex ListClient Lex.o ListClient.o List.o

checkClient: 
	valgrind --leak-check=full ./ListTest

checkLex:
	valgrind --leak-check=full Lex in3 blah3 
