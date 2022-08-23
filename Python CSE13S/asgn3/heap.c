#include "stats.h"
#include "stdbool.h"

// main function that sorts and sets the max child for heap sort//
uint32_t max_child(Stats *stats, uint32_t *A, uint32_t first, uint32_t last) {
    uint32_t left = 2 * first; // initializing left and right variables//
    uint32_t right = left + 1;
    if (right <= last && (cmp(stats, A[right - 1], A[left - 1]) > 0)) {
        return right;
    }
    return left;
}
// fixes heap sort function by sorting through first and last for max child//
void fix_heap(Stats *stats, uint32_t *A, uint32_t first, uint32_t last) {
    bool found = false;
    uint32_t mother = first;
    uint32_t great = max_child(stats, A, mother, last);
    //while loop for checking the array and swapping mother and great indexes//
    while ((mother <= last / 2) && (found == false)) {
        if (cmp(stats, A[mother - 1], A[great - 1]) < 0) {
            swap(stats, &A[mother - 1], &A[great - 1]);
            mother = great;
            great = max_child(stats, A, mother, last);
        } else {
            found = true;
        }
    }
}
// build heap function designed to call fix heap within a for loop//
void build_heap(Stats *stats, uint32_t *A, uint32_t first, uint32_t last) {
    for (uint32_t father = last / 2; father > first - 1; father -= 1) {
        fix_heap(stats, A, father, last);
    }
}
// main heap sort function that builds the heap and fixes it//
void heap_sort(Stats *stats, uint32_t *A, uint32_t n) {
    uint32_t first = 1;
    uint32_t last = n;
    build_heap(stats, A, first, last);
    for (uint32_t leaf = last; leaf > first; leaf -= 1) {
        swap(stats, &A[first - 1], &A[leaf - 1]);
        fix_heap(stats, A, first, leaf - 1);
    }
}
