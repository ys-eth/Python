# Assignment 6: Huffman Data Compression (README.md)

## Short description:

This assignment requires us to implement a Huffman encoder, decoder, node, priority queue, ADT, i/o module, and a stack structure. Within Huffman Data Compression, we must utilize optimal static encoding to assign the least amount of bits to a common symbol and the greatest number of bits to the least common symbol for an efficient Huffman data compression file.

## Build

To build manually, type "clang -Wall -Wextra -Werror -Wpedantic -o encode.o encode decode.o decode node.o pq.o code.o io.o stack.o huffman.o" on the command line. There will be an error in scanbuild that doesn't grant access to field 'left' results in a dereference of a null pointer. If this doesn't work, type "make" on the command line with the Makefile from the directory.

## Running

        ./encode ./decode 

## Cleaning

        To clean, use "rm -f encode.o encode decode.o decode node.o pq.o code.o io.o stack.o huffman.o" on the command line. If this doesn't work, type "clean" on the command line.
~                                                                
