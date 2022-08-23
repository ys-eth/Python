# Assignment 7: Author Identification (README.md)

## Short description:

This assignment requires us to implement a program that attempts to identify the most likely authors for an anonymous sample of text when given a large database of texts with known authors. In other words, we will be using an algorithm that’s commonly used in machine learning to identify authors of anonymous samples of text. This algorithm is also known as the k-nearest neighbor's algorithm. By utilizing this algorithm, we will classify samples of texts and determine which authors are most likely to have authored an anonymous sample of text.

## Build

To build manually, type "clang -Wall -Wextra -Werror -Wpedantic -o identify.o identify text.o texts bf.o bv.o ht.o node.o parser.o pq.o speck.o" on the command line. If this doesn't work, type "make" on the command line with the Makefile from the directory.

## Running

        ./identify

## Cleaning

        To clean, use "rm identify.o identify text.o  bf.o bv.o ht.o node.o parser.o pq.o speck.o" on the command line. If this doesn't work, type "clean" on the command line.
~

