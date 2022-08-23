# Assignment 4: The Game of Life (README.md)

## Short description:

	This assignment requires us to implement abstract data types to create and implement the Game of Life in C. The abstract data type will provide the abstraction for a universe, a finite 2-D grid of cells. This program will work in finite memory and will be using structures, constructors, and functions to develop the Game of Life. In addition, this program will sort through for loops and return the rows and columns that contain live & dead cells. These cells will then be printed through a function and displayed on a custom rows & columns board set by the user interface. Once ran, the program will generate the amount of live and dead cells on the Game of Life Board along with the forthcoming changes in the live/dead cells as the program undergoes multiple generations of changes.

## Build

        To build manually, type "clang -Wall -Wextra -Werror -Wpedantic -o life life.c" on the command line.
        If this doesn't work, type "make" on the command line with the Makefile from the directory.

## Running

        ./life

## Cleaning

        To clean, use "rm -f life.o life universe.o" on the command line.
        If this doesn't work, type "clean" on the command line.                                                               
