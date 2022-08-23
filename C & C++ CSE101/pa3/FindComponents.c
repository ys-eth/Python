/****************************************************************************************
*  Name: Yash Sharma
*  Cruz ID: yhsharma
*  Assignment Name: pa3
***************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Graph.h"
#include "List.h"

int main (int argc, char **argv) {
    int count = 0;
    if (argv[1] == NULL) {
        fprintf(stderr, "FindComponents.c program requires more argument inputs");
        exit(EXIT_FAILURE);
    }

    if (argv[2] == NULL) {
        fprintf(stderr, "FindComponents.c program requires less argument inputs");
        exit(EXIT_FAILURE);
    }

    FILE *infile = fopen(argv[1], "r");
    FILE *outfile = fopen(argv[2], "w");

    int v;
    int x;
    int y;
    fscanf(infile, "%d", &v);
    Graph G = newGraph(v);
    fscanf(infile, "%d %d", &x, &y);
    while (x != 0 && y != 0) {
        addArc(G, x, y);
        fscanf(infile, "%d %d", &x, &y);
    }
    fprintf(outfile, "Adjacency list representation of G:\n");
    printGraph(outfile, G);
    
    List A = newList();
    
    for (int i = 1; i < getOrder(G) + 1; i++) {
        append(A, i);
    }

    DFS(G, A);
    Graph B = transpose(G);
    DFS(B, A);
    List C = newList();
    moveFront(A);

    while (index(A) >= 0) {
        if (getParent(B, get(A)) == NIL) {
            count++;
        }
        moveNext(A);
    }

    moveBack(A);
    fprintf(outfile, "\n");
    fprintf(outfile, "G contains %d strongly connected components:", count);
    count = 0;
    while (index(A) >= 0) {
        prepend(C, get(A));
        if (getParent(B, get(A)) == NIL) {
            count++;
            fprintf(outfile, "\n");
            fprintf(outfile, "Component %d: ", count);
            printList(outfile, C);
            clear(C);
        }
        movePrev(A);
    }
}
