#include "batcher.h"
#include "heap.h"
#include "insert.h"
#include "quick.h"
#include "set.h"
#include "stats.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void usage(void) {
    fprintf(stderr, "SYNOPSIS\n"
                    "   A collection of comparison-based sorting algorithms.\n"
                    "\n"
                    "USAGE\n"
                    "   ./sort [-Haibhqn:p:r:] [-n length] [-p elements] [-r seed]\n"
                    "\n"
                    "OPTIONS\n"
                    "   -H              Display program help and usage.\n"
                    "   -a              Enable all sorts.\n"
                    "   -i              Enable Insertion Sort.\n"
                    "   -b              Enable Batcher Sort.\n"
                    "   -h              Enable Heap Sort.\n"
                    "   -q              Enable Quick Sort.\n"
                    "   -n length       Specify number of array elements (default: 100).\n"
                    "   -p elements     Specify number of elements to print (default: 100).\n"
                    "   -r seed         Specify random seed (default: 13371453).\n");
}

typedef enum { Insertion = 0, Batcher = 1, Heap = 2, Quick = 3 } Sorting;

int main(int argc, char **argv) {
    Set s = empty_set();
    uint32_t n = 100;
    uint32_t p = 100;
    uint32_t r = 13371453;
    uint32_t count = 0;
    int opt = 0;
    while ((opt = getopt(argc, argv, "Haibhqn:p:r")) != -1) {
        switch (opt) {
        case 'H': usage(); break;
        case 'a': s = complement_set(empty_set()); break;
        case 'i': s = insert_set(Insertion, s); break;
        case 'b': s = insert_set(Batcher, s); break;
        case 'h': s = insert_set(Heap, s); break;
        case 'q': s = insert_set(Quick, s); break;
        case 'n': n = strtod(optarg, NULL); break;
        case 'p': p = strtod(optarg, NULL); break;
        case 'r': r = strtod(optarg, NULL); break;
        default: usage(); return EXIT_FAILURE;
        }
    }
    uint32_t *A = (uint32_t *) malloc(n * sizeof(uint32_t));

    srandom(r);
    for (uint32_t i = 0; i < n; i += 1) {
        A[i] = random() & 0x3FFFFFFF;
    }
    if (member_set(Insertion, s)) {
        Stats stats = { 0, 0 };
        insertion_sort(&stats, A, n);
        if (p > n) {
            p = n;
        }
        printf("Insertion Sort, %d elements, %lu moves, %lu compares\n", n, stats.moves,
            stats.compares);
        for (uint32_t i = 0; i < p; i++) {
            if (count == 5) {
                count = 0;
                printf("\n");
            }
            printf("%13" PRIu32, A[i]);
            count++;
        }
        printf("\n");
    }

    srandom(r);
    for (uint32_t i = 0; i < n; i += 1) {
        A[i] = random() & 0x3FFFFFFF;
    }
    if (member_set(Heap, s)) {
        Stats stats = { 0, 0 };
        heap_sort(&stats, A, n);
        if (p > n) {
            p = n;
        }
        printf("Heap Sort, %d elements, %lu moves, %lu compares\n", n, stats.moves, stats.compares);
        for (uint32_t i = 0; i < p; i++) {
            if (count == 5) {
                count = 0;
                printf("\n");
            }
            printf("%13" PRIu32, A[i]);
            count++;
        }
        printf("\n");
    }

    srandom(r);
    for (uint32_t i = 0; i < n; i += 1) {
        A[i] = random() & 0x3FFFFFFF;
    }
    if (member_set(Quick, s)) {
        Stats stats = { 0, 0 };
        quick_sort(&stats, A, n);
        if (p > n) {
            p = n;
        }
        printf(
            "Quick Sort, %d elements, %lu moves, %lu compares\n", n, stats.moves, stats.compares);
        for (uint32_t i = 0; i < p; i++) {
            if (count == 5) {
                count = 0;
                printf("\n");
            }
            printf("%13" PRIu32, A[i]);
            count++;
        }
        printf("\n");
    }

    srandom(r);

    for (uint32_t i = 0; i < n; i += 1) {
        A[i] = random() & 0x3FFFFFFF;
    }
    if (member_set(Batcher, s)) {
        Stats stats = { 0, 0 };
        batcher_sort(&stats, A, n);
        if (p > n) {
            p = n;
        }
        printf(
            "Batcher Sort, %d elements, %lu moves, %lu compares\n", n, stats.moves, stats.compares);
        for (uint32_t i = 0; i < p; i++) {
            if (count == 5) {
                count = 0;
                printf("\n");
            }
            printf("%13" PRIu32, A[i]);
            count++;
        }
        printf("\n");
    }

    free(A);
    return 0;
}
