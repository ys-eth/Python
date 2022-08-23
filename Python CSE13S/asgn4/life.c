#include "universe.h"
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#define DELAY 50000

void usage(void) { // Usage function for the main program //
    fprintf(stderr,
        "SYNOPSIS\n"
        "   A program implementing the Game of Life in C.\n"
        "\n"
        "USAGE\n"
        "   ./life [-Htsn:i:o:] [-n generations] [-i input] [-o output]\n"
        "\n"
        "OPTIONS\n"
        "   -H              Display program help and usage.\n"
        "   -t              Specify that the Game of Life is to be played on a toroidal universe.\n"
        "   -s              Enabling this option means that nothing should be displayed by "
        "ncurses.\n"
        "   -n generations  Specify the number of generations that the universe goes through "
        "(default: 100).\n"
        "   -i input        Specify the input file to read in order to populate the universe "
        "(default: stdin).\n"
        "   -o output       Specify the output file to print the final state of the universe to "
        "(default: stdout).\n");
}

// Simple swap function that can swap the values of universeA with universeB using a temp function. //
void swap(Universe **universeA, Universe **universeB, bool toroidal) {
    Universe *tmp = uv_create(uv_rows(*universeA), uv_cols(*universeA), toroidal);
    //Universe *tmp = *universeA;
    uv_delete(tmp);
    tmp = *universeA;
    *universeA = *universeB;
    *universeB = tmp;
}

// main function for the life.c program //
int main(int argc, char **argv) {
    uint32_t n = 100; // initialized for number of generations //
    FILE *input = stdin; // initialized for input //
    FILE *output = stdout; // initialized for output//
    bool t = false; // initialized for a toroidal universe //
    bool s = false; // initialized for ncurses to not print anything //
    int opt = 0; // initialized for the getopt switch cases //
    uint32_t r; // initialized for integer of rows //
    uint32_t c; // initialized for integer of columns//

    // Getopt switch cases for each of the options //
    while ((opt = getopt(argc, argv, "Htsn:i:o:")) != -1) {
        switch (opt) {
        case 'H': usage(); break;
        case 't': t = true; break;
        case 's': s = true; break;
        case 'n': n = strtod(optarg, NULL); break;
        case 'i': input = fopen(optarg, "r"); break;
        case 'o': output = fopen(optarg, "w"); break;
        default: usage(); return EXIT_FAILURE;
        }
    }
    fscanf(input, "%d %d", &r, &c); // Scans the file and store the integer rows and columns //
    Universe *universeA = uv_create(r, c, t); // Creates the first universe //
    Universe *universeB = uv_create(r, c, t); // Creates the second universe //
    uv_populate(universeA, input); // Populates the universe with a file //
    fclose(input); // closes the file //

    // Creates a for loop that iterates through count and adds to it as the number of gens are greater than count //
    for (uint32_t count = 0; count < n; count++) {
        if (s == false) { // ncurses will be displayed //
            initscr(); // initializes the screen
            curs_set(FALSE); // hides the cursor
            clear();
            for (uint32_t ro = 0; ro < uv_rows(universeA);
                 ro += 1) { // for loop to check 1st condition in life rules //
                for (uint32_t co = 0; co < uv_cols(universeA); co += 1) {
                    if (uv_get_cell(universeA, ro, co) == true) {
                        mvprintw(ro, co, "o"); // prints the live cells //
                    } else {
                        mvprintw(ro, co, " "); // prints the dead cells //
                    }
                }
            }
            refresh(); // refreshes the window //
            usleep(DELAY); // adds a timer delay to view data cells smoothly //
        }
        for (uint32_t r = 0; r < uv_rows(universeA); r++) {
            for (uint32_t c = 0; c < uv_cols(universeA); c++) {
                if (uv_get_cell(universeA, r, c)) {
                    if (uv_census(universeA, r, c) == 2 || uv_census(universeA, r, c) == 3) {
                        uv_live_cell(universeB, r, c);
                    } else {
                        uv_dead_cell(universeB, r, c);
                    }
                } else {
                    if (uv_census(universeA, r, c) == 3) {
                        uv_live_cell(universeB, r, c);
                    } else {
                        uv_dead_cell(universeB, r, c);
                    }
                }
            }
        }
        /*    
	for (uint32_t r = 0; r < uv_rows(universeA); r += 1) { // for loop to check 2nd condition in life rules//
	    for (uint32_t c = 0; c < uv_cols(universeA); c += 1) { // Creates a second for loop to iterate through the cols of universeA //
	        if (uv_get_cell(universeA, r, c) == true) { // checks if cell is alive // 
	            if (uv_census(universeA, r, c) == 2 || uv_census(universeA, r, c) == 3) { // if cells is alive and has 2 or 3 neighbors //
	                printf("%d\n", uv_census(universeA, r, c));
		        uv_live_cell(universeB, r, c); // print live cell // 
	            } else {
                        printf("hi%d\n", uv_census(universeA, r, c));
			uv_dead_cell(universeB, r, c); // else print dead cell // 
	            }
		} else {
                    // if cell is not alive and has 3 neighbors, then print live cell //
	            if (uv_census(universeA, r, c) == 3) {
                        printf("bye%d\n", uv_census(universeA, r, c));
			uv_live_cell(universeB, r, c);
	            } else {
                        printf("wtf%d\n", uv_census(universeA, r, c));
			uv_dead_cell(universeB, r, c); // print dead cell//
	            }
                }
            }
       	}
	*/
        swap(&universeA, &universeB, t); // swaps universeA and universe B in a toroidal universe //
    }
    endwin(); // closes screen //
    uv_print(universeA, output); // prints out output file //
    uv_delete(universeA);
    uv_delete(universeB);
    fclose(output); // closes output file //
    return 0;
}
