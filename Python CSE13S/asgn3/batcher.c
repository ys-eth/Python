#include "stats.h"

//A function for bit length that counts the amount of bits being processed//
uint32_t bl(uint32_t n) {
    uint32_t count = 0;
    while (n > 0) {
        count += 1;
        n = n / 2;
    }
    return count;
}

//checks if the array of i is greater than j, if so then swaps places//
void comparator(Stats *stats, uint32_t *A, uint32_t i, uint32_t j) {

    if (cmp(stats, A[i], A[j]) > 0) {
        swap(stats, &A[i], &A[j]);
    }
}
//main function for batcher sort, contains all sorting and algorithms//
void batcher_sort(Stats *stats, uint32_t *A, uint32_t n) {
    if (n == 0) {
        return;
    } //intializing all variables//
    uint32_t t = bl(n);
    uint32_t p = 1 << (t - 1);
    uint32_t q;
    uint32_t r;
    uint32_t d;
    //sets a while loop to check if the parameter is greater than 0//
    while (p > 0) {
        q = 1 << (t - 1);
        r = 0;
        d = p;
        //while loop designed for the comparator function//
        while (d > 0) {
            for (uint32_t i = 0; i < n - d; i++) {
                if ((i & p) == r) {
                    comparator(stats, A, i, i + d); //compares the given value within the iterator//
                }
            }
            d = q - p;
            q >>= 1;
            r = p;
        }
        p >>= 1;
    }
}
