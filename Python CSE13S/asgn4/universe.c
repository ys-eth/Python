#include "universe.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

// Creates a structure as the basis for the universe //
struct Universe {
    uint32_t rows;
    uint32_t cols;
    bool **grid;
    bool toroidal;
};

Universe *uv_create(uint32_t rows, uint32_t cols, bool toroidal) {
    // Creates universe as a pointer//
    Universe *u = (Universe *) malloc(sizeof(Universe));
    u->rows = rows;
    u->cols = cols;
    u->grid = (bool **) calloc(rows, sizeof(bool *)); // allocates memory//
    for (uint32_t r = 0; r < rows; r += 1) {
        u->grid[r] = (bool *) calloc(cols, sizeof(bool)); // initializes the matrix //
    }
    u->toroidal = toroidal;
    return u;
}

// allows for universe to be deleted//
void uv_delete(Universe *u) {
    for (uint32_t r = 0; r < uv_rows(u); r += 1) {
        free(u->grid[r]); // frees the index of r from the grid and the universe //
    }
    free(u->grid); // frees the grid from the pointer of universe//
    free(u); // frees the universe //
}

// holds the count for the amount of rows in a universe//
uint32_t uv_rows(Universe *u) {
    return u->rows;
}

// holds the count for the amount of cols in a universe//
uint32_t uv_cols(Universe *u) {
    return u->cols;
}

// displays the number of live cells in a universe //
void uv_live_cell(Universe *u, uint32_t r, uint32_t c) {
    //printf("hi\n");
    //printf("%d\n", r >= 0);
    if (r >= 0 && c >= 0 && r < uv_rows(u) && c < uv_cols(u)) {
        u->grid[r][c] = true; // sets the cell to live //
    }
}

// displays the number of dead cells in a universe //
void uv_dead_cell(Universe *u, uint32_t r, uint32_t c) {
    if ((r >= 0) && (c >= 0) && (uv_rows(u) > r) && (uv_cols(u) > c)) {
        u->grid[r][c] = false; // sets the cell to dead //
    }
}

// returns the value held by the rows and columns //
bool uv_get_cell(Universe *u, uint32_t r, uint32_t c) {
    if ((r < uv_rows(u)) && (c < uv_cols(u))) {
        return u->grid[r][c];
    } else {
        return false;
    }
}

// populates the universe using the data acquired from the live cells //
bool uv_populate(Universe *u, FILE *infile) {

    uint32_t r;
    uint32_t c;
    while (fscanf(infile, "%d %d", &r, &c)
           != EOF) { // Scans through a file and returns rows and cols//
        uv_live_cell(u, r, c);
        if ((r < 0) || (c < 0) || (uv_rows(u) < r) || (uv_cols(u) < c)) {
            return false;
        }
    }
    return true;
}

uint32_t uv_census(Universe *u, uint32_t r, uint32_t c) {
    uint32_t val = 0;
    uint32_t front
        = (r + 1)
          % uv_rows(
              u); // Create 4 integers to check the surrounding neighbors in a toroidal universe//
    uint32_t minus = (r + uv_rows(u) - 1) % uv_rows(u);
    uint32_t frontc = (c + 1) % uv_cols(u);
    uint32_t minusc = (c + uv_cols(u) - 1) % uv_cols(u);

    uint32_t front1
        = (r + 1); // Create 4 integers to check the surrounding neighbors in a flat universe//
    uint32_t minus1 = (r - 1);
    uint32_t frontc1 = (c + 1);
    uint32_t minusc1 = (c - 1);

    uint32_t array_rows[8] = { minus, minus, minus, r, r, front, front,
        front }; // Sort the toroidal neighbors into rows //
    uint32_t array_cols[8] = { minusc, c, frontc, minusc, frontc, minusc, c,
        frontc }; // Sort the toroidal neighbors into cols //

    uint32_t array_rows1[8] = { minus1, minus1, minus1, r, r, front1, front1,
        front1 }; // Sort the neighbors into rows //
    uint32_t array_cols1[8] = { minusc1, c, frontc1, minusc1, frontc1, minusc1, c,
        frontc1 }; // Sort the neighbors into cols //

    // For loop that iterates through toroidal and flat universe, updates val //
    if (u->toroidal == true) {
        for (uint32_t j = 0; j < 8; j++) {
            // printf("%d\n", uv_get_cell(u, array_rows[j], array_cols[j]));
            if (uv_get_cell(u, array_rows[j], array_cols[j]) == true) {
                //       printf("%d\n", uv_get_cell(u, array_rows[j], array_cols[j]));
                val += 1;
            }
        }
    } else {
        for (uint32_t i = 0; i < 8; i++) {
            if (uv_get_cell(u, array_rows1[i], array_cols1[i]) == true) {
                val++;
            }
        }
    }
    return val;
}

// Prints the universe to an outfile //

void uv_print(Universe *u, FILE *outfile) {
    for (uint32_t i = 0; i < uv_rows(u); i += 1) { // checks the rows for universe //
        for (uint32_t j = 0; j < uv_cols(u); j += 1) { // checks the cols for universe //
            if (uv_get_cell(u, i, j)
                == true) { // checks if the cell is alive, then prints a circle. //
                fprintf(outfile, "o");
            } else {
                fprintf(outfile, "."); // if cell is dead, then prints a dot. //
            }
        }
        fprintf(outfile, "\n"); // new line created to separate the rows and cols from each other//
    }
}
