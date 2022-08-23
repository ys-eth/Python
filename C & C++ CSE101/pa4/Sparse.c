/****************************************************************************************
  *  Name: Yash Sharma
  *  Cruz ID: yhsharma
  *  Assignment Name: pa4
*****************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "List.h"
#include "Matrix.h"

int main (int argc, char **argv) {
    double f;
    int a, b, c, d, e;
    Matrix F, G, H, I, J, K, L, M;
    if (argv[1] == NULL) {
        fprintf(stderr, "Sparse.c program requires more argument inputs");
        exit(EXIT_FAILURE);
    }

    if (argv[2] == NULL) {
        fprintf(stderr, "Sparse.c program requires less argument inputs");
        exit(EXIT_FAILURE);
    }

    FILE *infile = fopen(argv[1], "r");
    FILE *outfile = fopen(argv[2], "w");
    fscanf(infile, "%d %d %d\n", &a, &b, &c);
    Matrix N = newMatrix(a);
    Matrix O = newMatrix(a);

    for (int i = 1; i <= b; i++) {
        fscanf(infile, "%d %d %lf\n", &d, &e, &f);
        changeEntry(N, d, e, f);
    }
    for (int i = 1; i <= c; i++) {
        fscanf(infile, "%d %d %lf\n", &d, &e, &f);
        changeEntry(O, d, e, f);
    }
    fprintf(outfile, "A has %d non-zero entries:\n", NNZ(N));
    printMatrix(outfile, N);
    fprintf(outfile, "\n");

    fprintf(outfile, "B has %d non-zero entries:\n", NNZ(O));
    printMatrix(outfile, O);
    fprintf(outfile, "\n");

    fprintf(outfile, "(1.5)*A =\n");
    F = scalarMult(1.5, N);
    printMatrix(outfile, F);
    fprintf(outfile, "\n");

    fprintf(outfile, "A+B =\n");
    G = sum(N, O);
    printMatrix(outfile, G);
    fprintf(outfile, "\n");

    fprintf(outfile, "A+A =\n");
    H = sum(N, N);
    printMatrix(outfile, H);
    fprintf(outfile, "\n");

    fprintf(outfile, "B-A =\n");
    I = diff(O, N);
    printMatrix(outfile, I);
    fprintf(outfile, "\n");

    fprintf(outfile, "A-A =\n");
    J = diff(N, N);
    printMatrix(outfile, J);
    fprintf(outfile, "\n");

    fprintf(outfile, "Transpose(A) =\n");
    K = transpose(N);
    printMatrix(outfile, K);
    fprintf(outfile, "\n");

    fprintf(outfile, "A*B =\n");
    L = product(N, O);
    printMatrix(outfile, L);
    fprintf(outfile, "\n");

    fprintf(outfile, "B*B =\n");
    M = product(O, O);
    printMatrix(outfile, M);
    fprintf(outfile, "\n");

    fclose(infile);
    fclose(outfile);
    freeMatrix(&N);
    freeMatrix(&O);
    freeMatrix(&F);
    freeMatrix(&G);
    freeMatrix(&H);
    freeMatrix(&I);
    freeMatrix(&J);
    freeMatrix(&K);
    freeMatrix(&L);
    freeMatrix(&M);
    return 0;
}

