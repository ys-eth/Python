#include "defines.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "code.h"

/*typedef struct {
    uint32_t top;
    uint8_t bits[MAX_CODE_SIZE];
} Code;
*/

Code code_init(void) {
    Code code1 = { 0 }; // Creates a constructor called Code on the stack
    code1.top = 0; // Sets the top equal to 0
    return code1; // return the Code
}

uint32_t code_size(Code *c) {
    return c->top; // sets the top of the code
}

bool code_empty(Code *c) {
    return c->top == 0; // sets the top of the code equal to 0
}

bool code_full(Code *c) {
    if (c) {
        return c->top
               == MAX_CODE_SIZE; // sets the top of the code equal to the number of bits in the code minus 1
    }
    return true;
}

bool code_set_bit(Code *c, uint32_t i) {
    if (i > 255 || i < 0) { // checks if the bits are in the range
        return false;
    }
    c->bits[i / 8]
        |= (0x1 << i % 8); // Divides 8 from the number of bits in an index from the pointer c
    return true;
}

bool code_clr_bit(Code *c, uint32_t i) {
    if (i > 255 || i < 0) { // checks if the bits are in the range
        return false;
    }
    c->bits[i / 8]
        &= ~(0x1 << i % 8); // Divide 8 from the number of bits in an index from the pointer c
    return true;
}
bool code_get_bit(Code *c, uint32_t i) {
    if (i > 255 || i < 0 || c->bits[i / 8] == 0) { //checks if the bits are in the range
        return false;
    }
    if ((c->bits[i / 8] >> i % 8)
        & 0x1) { // Divide 8 from the number of bits in an index from the pointer c
        return true;
    }
    return false;
}

bool code_push_bit(Code *c, uint8_t bit) {
    if (code_full(c)) { // if the code is full, then return false
        return false;
    }
    if (bit == 1) {
        code_set_bit(c, c->top); // calls the set bit function and sets the bit
        c->top++;
    } else {
        c->top++;
    }
    return true;
}

// sets the bit, and increments the top

bool code_pop_bit(Code *c, uint8_t *bit) {
    if (code_empty(c)) { //checks if the code is empty, if so then return false
        return false;
    }
    c->top--; // subtracts from the top
    if (code_get_bit(c, c->top)) {
        *bit = 1;
    } else {
        *bit = 0;
    }
    return true; // else return true.
}

// grab the bit from get bit and decrement the top

void code_print(
    Code *c) { // debugging function for the program, checks if the code is full or empty.
    printf("%u\n", c->top);
    if (code_full(c)) {
        printf("code is full");
    }
    if (code_empty(c)) {
        printf("code is empty");
    }
}
