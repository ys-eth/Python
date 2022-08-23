#include "quick.h"

#include "stats.h"

// function partition that contains parameters: stats, array, low, and high//
uint32_t partition(Stats *stats, uint32_t *A, uint32_t low, uint32_t high) {
    uint32_t i = low - 1;
    for (
        uint32_t j = low; j < high;
        j++) { //Set a for loop to check whether j = low and to run it till j is less than high, incrementing by 1 each time//

        if (cmp(stats, A[j - 1], A[high - 1]) < 0) { // compares the two arrays//
            i += 1;
            swap(stats, &A[i - 1], &A[j - 1]); // swaps arrays//
        }
    }
    swap(stats, &A[i], &A[high - 1]);
    return i + 1;
}

// quick sorter function used to sort the partition values//
void quick_sorter(Stats *stats, uint32_t *A, uint32_t low, uint32_t high) {
    if (low < high) {
        uint32_t p = partition(stats, A, low, high);
        quick_sorter(stats, A, low, p - 1); //calls quick sorter function for p - 1//
        quick_sorter(stats, A, p + 1, high); // calls quick sorter function for p + 1//
    }
    return;
}

//main quick sort function that calls quick_sorter to do sorting//
void quick_sort(Stats *stats, uint32_t *A, uint32_t n) {
    quick_sorter(stats, A, 1, n);
}
