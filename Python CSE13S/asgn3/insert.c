#include "insert.h"

//main insertion sort function that takes in 3 parameters to check if the array is increasing order//
void insertion_sort(Stats *stats, uint32_t *A, uint32_t n) {
    for (uint32_t i = 1; i < n; i += 1) { //Checks the range between 1 and the len of array//
        uint32_t j = i;
        uint32_t temp = move(stats, A[i]); //initializes and moves value to a temp variable//
        while (j > 0 && cmp(stats, temp, A[j - 1]) < 0) { //
            A[j] = move(stats, A[j - 1]);
            j -= 1;
        }
        A[j] = move(stats, temp); // moves stats and temp into the array j.//
    }
    return;
}
