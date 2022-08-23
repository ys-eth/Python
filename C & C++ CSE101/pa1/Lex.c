/****************************************************************************************
  *  Name: Yash Sharma
  *  Cruz ID: yhsharma
  *  Assignment Name: pa1
*****************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "List.h"

int main (int argc, char **argv) {
    int count = 0;
    char buffer[4096];
    if (argv[1] == NULL) {
        fprintf(stderr, "Lex.c program requires more argument inputs");
        exit(EXIT_FAILURE);
    }
    if (argv[2] == NULL) {
        fprintf(stderr, "Lex.c program requires less argument inputs");
        exit(EXIT_FAILURE);
    }
    FILE *infile = fopen(argv[1], "r");
    FILE *outfile = fopen(argv[2], "w");
    while (fgets(buffer, sizeof(buffer), infile) != NULL) {
        count++;
    }
    fseek(infile, 0L, SEEK_SET);
    char **arr = (char **) malloc(count * sizeof(char *));
    for (int i = 0; i < count; i++) {
        fgets(buffer, sizeof(buffer), infile);
        arr[i] = (char *) malloc((strlen(buffer) + 1) * sizeof(char));
        strncpy(arr[i], buffer, strlen(buffer) + 1);
    }
    List L = newList();
    for (int i = 0; i < count; i++) {
        moveFront(L);
        while (index(L) >= 0) {
            if (strcmp(arr[i], arr[get(L)]) < 0 && length(L) <= i) {
                insertBefore(L, i);
            }
            moveNext(L);
        }
        if (length(L) == i) {
            append(L, i);
        }
    }
    moveFront(L);
    for (int i = 0; i < count; i++) {
        fprintf(outfile, "%s", arr[get(L)]);
        moveNext(L);
    }
    fclose(infile);
    fclose(outfile);
    freeList(&L);
    for (int i = 0; i < count; i++) {
        free(arr[i]);
    }
    free(arr);
    arr = NULL;
    return 0;
}
