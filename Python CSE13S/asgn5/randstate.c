#include <stdint.h>
#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>

gmp_randstate_t state;

// initializes the randome state seed //
void randstate_init(uint64_t seed) {
    srandom(seed);
    gmp_randinit_mt(state);
    gmp_randseed_ui(state, seed);
}
//clears random state variable//
void randstate_clear(void) {
    gmp_randclear(state);
}
