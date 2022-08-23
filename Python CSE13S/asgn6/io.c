#include "code.h"
#include "io.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdint.h>
#include "defines.h"
#include <stdlib.h>

static uint32_t byte = 0;
static size_t index = 0;
static uint8_t mask = 0x80;
static size_t maxIndex = 0;
static uint8_t buffer[BLOCK];
uint64_t bytes_read;
uint64_t bytes_written;

int read_bytes(int infile, uint8_t *buf, int nbytes) {

    int bytes1 = 1;
    int total_bytes = 0;
    while (bytes1 > 0) { // keeps looping for the number of bytes that are greater than 0
        bytes1 = read(infile, buf, nbytes); // reads the file for nbytes using the buffer
        bytes_read += bytes1; // adds to the number of bytes read
        total_bytes += bytes1; // increments the total bytes by the count
    }
    return total_bytes; // returns the total
}

int write_bytes(int outfile, uint8_t *buf, int nbytes) {

    ssize_t bytes1 = 1;
    int total_bytes = 0;
    while (bytes1 > 0) { // keeps looping for the number of bytes that are greater than 0
        bytes1 = write(outfile, buf,
            nbytes
                - total_bytes); // writes the file for nybtes which is subtracting the total bytes
        bytes_written += bytes1; // increments the bytes writtens
        total_bytes += bytes1; // adds those bytes written to the total bytes
    }
    return total_bytes; // returns the total
}

bool read_bit(int infile, uint8_t *bit) {

    //  when buffer is empty, read in a block of bytes. From block of bytes, return each byte bit by bit. //

    if (index == 0
        || index
               == BLOCK
                      * 8) { // checks if the index equals 0 or if the index is equal to the max index
        maxIndex = read_bytes(infile, buffer, BLOCK); // reads the bytes into max Index

        if (maxIndex == 0) { // checks if max index is 0, if so then returns false
            return false;
        }
    }

    if ((buffer[index / 8] >> index % 8)
        & 0x1) { // checks if the index of the buffer and mask is not equal to 0
        *bit = 1;
    } else {

        *bit = 0; // else sets the bit equal to 0
    }
    index++;
    return true;
}

void write_code(int outfile, Code *c) {

    for (size_t i = 0; i < code_size(c);
         i++) { // loops through the size of the code and increments the iterator
        if (code_get_bit(c, i) == 1) { // if the bit equals 1, mask the byte
            byte |= mask;
        }
        mask >>= 1; // adds 1 to the mask
        if (mask == 0) { // if the mask is empty
            buffer[index++] = byte; // add to the index in the buffer
            byte = 0;
            mask = 0x80;
            if (index
                == BLOCK) { // if index is equal to block, write bytes to the index and set the index to 0 after
                write_bytes(outfile, buffer, BLOCK);
                index = 0;
            }
        }
    }
}

void flush_codes(int outfile) {
    if (mask
        != 0x80) { // if the mask is not equal to an 8 byte set, then increment the index of the buffer by 1
        buffer[index++] = byte;
    }
    write_bytes(outfile, buffer, index); //write the bytes to the outfile
}
