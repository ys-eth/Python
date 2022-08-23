#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include "bv.h"

struct BitVector {
    uint32_t length;
    uint8_t *vector;
};

BitVector *bv_create(uint32_t length) {
    BitVector *bitv
        = (BitVector *) malloc(sizeof(BitVector)); // allocates memory for the bit vector
    if (bitv != NULL) { // if the bitvector is not NULL
        bitv->length = length; // initialize length
        bitv->vector = (uint8_t *) calloc(
            (length + 7) / 8, sizeof(uint8_t)); //allocate memory for the vector
        return bitv; // return the bitvector
    }
    return NULL;
}

void bv_delete(BitVector **bv) {
    free(((*bv)->vector)); // free the pointer to the bitvector
    (*bv)->vector = NULL; // set the pointer of the bv to null
    free((*bv)); // free the bitvector
    *bv = NULL; // null the bitvector
}

uint32_t bv_length(BitVector *bv) {
    return bv->length; // return the length of the bit vector
}

bool bv_set_bit(BitVector *bv, uint32_t i) {
    if (i > bv_length(bv) || i < 0) { // checks if the bits are in the range
        return false;
    }
    bv->vector[i / 8]
        |= (0x1 << i % 8); // Divides 8 from the number of bits in an index from the pointer
    return true;
}

bool bv_clr_bit(BitVector *bv, uint32_t i) {
    if (i > bv_length(bv) || i < 0) { // checks if the bits are in the range
        return false;
    }
    bv->vector[i / 8]
        &= ~(0x1 << i % 8); // Divide 8 from the number of bits in an index from the pointer
    return true;
}

bool bv_get_bit(BitVector *bv, uint32_t i) {
    if (i > bv_length(bv) || i < 0) { //checks if the bits are in the range
        return false;
    }
    if ((bv->vector[i / 8] >> i % 8)
        & 0x1) { // Divide 8 from the number of bits in an index from the pointer
        return true;
    }
    return false;
}

void bv_print(BitVector *bv) {
    for (uint8_t i = 0; i < bv_length(bv); i++) { // loops through the length of the bitvector
        if (bv_get_bit(bv, i) == true) {
            printf("1 [%u]\n", i); // prints 1 if the binary value is 1
        } else {
            printf("0 [%u]\n", i); // prints 0 if the binary value is 0
        }
    }
}
