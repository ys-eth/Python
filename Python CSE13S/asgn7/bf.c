#include "bv.h"
#include "bf.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include "salts.h"
#include "ht.h"
#include "speck.h"

struct BloomFilter {
    uint64_t primary[2]; // sets the parameters for the bloom filter salts
    uint64_t secondary[2];
    uint64_t tertiary[2];
    BitVector *filter;
};

BloomFilter *bf_create(uint32_t size) {
    BloomFilter *bloom
        = (BloomFilter *) malloc(sizeof(BloomFilter)); // allocates memory for the bloom filter
    if (bloom != NULL) {
        bloom->primary[0] = SALT_PRIMARY_LO; // sets the lower salt
        bloom->primary[1] = SALT_PRIMARY_HI; // set the higher salt

        bloom->secondary[0] = SALT_SECONDARY_LO; // sets the lower salt
        bloom->secondary[1] = SALT_SECONDARY_HI; // sets the higher salt

        bloom->tertiary[0] = SALT_TERTIARY_LO; // sets the lower salt
        bloom->tertiary[1] = SALT_TERTIARY_HI; // sets the higher salt

        bloom->filter = bv_create(size); // creates the size for the bloom filter
        return bloom;
    }
    return NULL;
}

void bf_delete(BloomFilter **bf) {
    bv_delete(&(*bf)->filter); // deletes the bloom filter pointer
    free(*bf);
    *bf = NULL;
}

uint32_t bf_size(BloomFilter *bf) {
    return (bv_length(bf->filter)); // returns the length of the bloom filter
}

void bf_insert(BloomFilter *bf, char *word) {
    uint32_t index1 = hash(bf->primary, word) % bf_size(bf); // sets the index for the primary salt
    uint32_t index2
        = hash(bf->secondary, word) % bf_size(bf); // sets the index for the secondary salt
    uint32_t index3
        = hash(bf->tertiary, word) % bf_size(bf); // sets the index for the tertiary salt

    bv_set_bit(bf->filter, index1); // sets the bit for index 1
    bv_set_bit(bf->filter, index2); // sets the bit for index 2
    bv_set_bit(bf->filter, index3); // sets the bit for index 3
}

bool bf_probe(BloomFilter *bf, char *word) {
    uint32_t count = 0;
    uint32_t index1 = hash(bf->primary, word) % bf_size(bf); // sets the index for the primary salt
    uint32_t index2
        = hash(bf->secondary, word) % bf_size(bf); // sets the index for the secondary salt
    uint32_t index3
        = hash(bf->tertiary, word) % bf_size(bf); // sets the index for the tertiary salt

    if (bv_get_bit(bf->filter, index1) == true) { // gets the bit for the filter at index 1
        count++;
    }
    if (bv_get_bit(bf->filter, index2) == true) { // gets the bit for the filter at index 2
        count++;
    }
    if (bv_get_bit(bf->filter, index3) == true) { // gets the bit for the filter at index 3
        count++;
    }
    if (count == 3) {
        return true;
    }
    return false;
}

void bf_print(BloomFilter *bf) {
    bv_print(bf->filter); // prints the bloom filter
}
