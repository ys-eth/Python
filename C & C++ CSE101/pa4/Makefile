# /****************************************************************************************
# *  Name: Yash Sharma
# *  Cruz ID: yhsharma
# *  Assignment Name: pa4
# *****************************************************************************************/

#------------------------------------------------------------------------------
#  Makefile for CSE 101 Programming Assignment 4
#
#  make                     makes Sparse
#  make Matrix Client       makes MatrixClient
#  make clean               removes binaries
#  make checkSparse         tests Sparse for memory leaks on in7
#  make checkClient         tests MatrixClient for memory leaks
#------------------------------------------------------------------------------

BASE_SOURCES   = Matrix.c List.c
BASE_OBJECTS   = Matrix.o List.o
HEADERS        = Matrix.h List.h
COMPILE        = gcc -std=c17 -Wall -c
LINK           = gcc -std=c17 -Wall -o
REMOVE         = rm -f
MEMCHECK       = valgrind --leak-check=full

Sparse : Sparse.o $(BASE_OBJECTS)
	$(LINK) Sparse Sparse.o $(BASE_OBJECTS)

MatrixClient : MatrixClient.o $(BASE_OBJECTS)
	$(LINK) MatrixClient MatrixClient.o $(BASE_OBJECTS)

MatrixTest : MatrixTest.o $(BASE_OBJECTS)
	$(LINK) MatrixTest MatrixTest.o $(BASE_OBJECTS)

MatrixTest.o : MatrixTest.c $(HEADERS)
	$(COMPILE) MatrixTest.c

ListTest : ListTest.o List.o
	$(LINK) ListTest ListTest.o List.o

ListTest.o : ListTest.c List.h
	$(COMPILE) ListTest.c

Sparse.o : Sparse.c $(HEADERS)
	$(COMPILE) Sparse.c

MatrixClient.o : MatrixClient.c $(HEADERS)
	$(COMPILE) MatrixClient.c

$(BASE_OBJECTS) : $(BASE_SOURCES) $(HEADERS)
	$(COMPILE) $(BASE_SOURCES)

clean :
	$(REMOVE) Sparse MatrixClient MatrixTest ListTest Sparse.o MatrixClient.o MatrixTest.o ListTest.o $(BASE_OBJECTS)

checkSparse : Sparse
	$(MEMCHECK) Sparse in7 junk7

checkClient : MatrixClient
	$(MEMCHECK) MatrixClient
