/****************************************************************************************
  *  Name: Yash Sharma
  *  Cruz ID: yhsharma
  *  Assignment Name: pa4
*****************************************************************************************/

#include <stdbool.h>
#include "Matrix.h"
#include "List.h"
#include <assert.h>

typedef struct EntryObj *Entry;

typedef struct EntryObj {
    double data;
    int cols;
 } EntryObj;

typedef struct MatrixObj {
    List *alist;
    int size;
    int NNZ;
} MatrixObj;

Entry newEntry(double data, int cols) {
    Entry x = malloc(sizeof(EntryObj));
    assert(x != NULL);
    x->data = data;
    x->cols = cols;
    return x;
}

void freeEntry(Entry* pE) {
    if (pE != NULL) {
        free(*pE);
        *pE = NULL;
    }
}

Matrix newMatrix(int n) {
    Matrix M = malloc(sizeof(MatrixObj));
    M->alist = malloc((n + 1) * sizeof(List));
    for (int i = 0; i < (n + 1); i++) {
        M->alist[i] = newList();
    }
    M->size = n;
    M->NNZ = 0;
    return M;
}

void freeMatrix(Matrix *pM) {
    if (pM != NULL && *pM != NULL) {
        makeZero(*pM);
        for (int i = 0; i < (*pM)->size; i++) {
            freeList(&(*pM)->alist[i]);
        }
        free((*pM)->alist);
        free(*pM);
        *pM = NULL;
    }
}

int size(Matrix M) {
    return M->size;
}

int NNZ(Matrix M) {
    return M->NNZ;
}

int equals(Matrix A, Matrix B) {
    if (A == B) {
        return 1;
    }
    if (size(A) != size(B)) {
        return 0;
    }
    if (NNZ(A) != NNZ(B)) {
        return 0;
    }
    for (int i = 1; i < size(A) + 1; i++) {
        if (length(A->alist[i]) != length(B->alist[i])) {
            return 0;
        }
        moveFront(A->alist[i]);
        moveFront(B->alist[i]);
        while (index(A->alist[i]) >= 0 || index(B->alist[i]) >= 0){
            Entry a = (Entry) get(A->alist[i]);
            Entry b = (Entry) get(B->alist[i]);
            if (a->cols != b->cols) {
                return 0;
            }
            if (a->data != b->data) {
                return 0;
            }
            moveNext(A->alist[i]);
            moveNext(B->alist[i]);
        }
    }
    return 1;
}

void changeEntry(Matrix M, int i, int j, double x) {
    if ((size(M) < i || i < 1) || (size(M) < j || j < 1)) {
        fprintf(stderr, "changeEntry Error: calling changeEntry() precondition not met");
        exit(EXIT_FAILURE);
    }
    moveFront(M->alist[i]);
    while (index(M->alist[i]) >= 0) {
        Entry a = (Entry) get(M->alist[i]);
        if (a->cols > j) {
            Entry y = newEntry(x, j);
            insertBefore(M->alist[i], y);
            M->NNZ++;
            return;
        }
        if (j == a->cols) {
            freeEntry(&a);
            delete(M->alist[i]);
            M->NNZ--;
            return;
        }
        if (x != 0 && a->cols == j) {
            a->data = x;
            return;
        }
        moveNext(M->alist[i]);
    }
    if (x != 0) {
        Entry y = newEntry(x, j);
        append(M->alist[i], y);
        M->NNZ++;
    }
    return;
}

Matrix scalarMult(double x, Matrix A) {
    Matrix N = newMatrix(size(A));
    double temp;
    for (int i = 1; i < size(A) + 1; i++) {
        if (length(A->alist[i]) > 0) {
            moveFront(A->alist[i]);
            while (index(A->alist[i]) >= 0) {
                Entry v = get(A->alist[i]);
                temp = x * v->data;
                changeEntry(N, i, v->cols, temp);
                moveNext(A->alist[i]);
            }
        }
    }
    return N;
}

void printMatrix(FILE* out, Matrix M) {
    for (int i = 1; i < size(M) + 1; i++) {
        if (length(M->alist[i]) > 0) {
            moveFront(M->alist[i]);
            fprintf(out, "%d: ", i);
            while (index(M->alist[i]) >= 0) {
                Entry v = get(M->alist[i]);
                fprintf(out, "(%d, %.1f) ", v->cols, v->data);
                moveNext(M->alist[i]);
            }
            fprintf(out, "\n");
        }
    }
}

void makeZero(Matrix M) {
    if (M == NULL) {
        fprintf(stderr, "makeZero Error: calling makeZero() precondition not met");
        exit(EXIT_FAILURE);
    }
    for (int i = 1; i < size(M) + 1; i++) {
        moveFront(M->alist[i]);
        while (index(M->alist[i]) >= 0) {
            Entry x = get(M->alist[i]);
            freeEntry(&x);
            moveNext(M->alist[i]);
        }
        clear(M->alist[i]);
    }
    M->NNZ = 0;
}

Matrix transpose(Matrix A) {
    Matrix N = newMatrix(size(A));
    for (int i = 1; i < size(A) + 1; i++) {
        if (length(A->alist[i]) > 0) {
            moveFront(A->alist[i]);
            while (index(A->alist[i]) >= 0) {
                Entry v = get(A->alist[i]);
                changeEntry(N, v->cols, i, v->data);
                moveNext(A->alist[i]);
            }
        }
    }
    return N;
}

Matrix sum(Matrix A, Matrix B) {
    if (size(A) != size(B)) {
        fprintf(stderr, "sum Error: calling sum() precondition not met");
        exit(EXIT_FAILURE);
    }
    if (A == B) {
        Matrix s = scalarMult(2, A);
        return s;
    }
    Matrix Y = newMatrix(size(A));
    for (int i = 1; i < size(A) + 1; i++) {
        moveFront(A->alist[i]);
        moveFront(B->alist[i]);
        while (index(A->alist[i]) >= 0 && index(B->alist[i]) >= 0) {
            Entry v = get(A->alist[i]);
            Entry w = get(B->alist[i]);
            if (v->cols > w->cols) {
                changeEntry(Y, i, w->cols, w->data);
                 moveNext(B->alist[i]);
            }
            else if (v->cols < w->cols) {
                changeEntry(Y, i, v->cols, v->data);
                 moveNext(A->alist[i]);
            }
            else if (v->cols == w->cols) {
                changeEntry(Y, i, v->cols, (v->data + w->data));
                moveNext(A->alist[i]);
                moveNext(B->alist[i]);
            }
        }
        while (index(A->alist[i]) >= 0 && index(B->alist[i]) < 0) {
            Entry v = get(A->alist[i]);
            changeEntry(Y, i, v->cols, v->data);
            moveNext(A->alist[i]);
        }
        while (index(A->alist[i]) <0  && index(B->alist[i]) >= 0) {
            Entry w = get(B->alist[i]);
            changeEntry(Y, i, w->cols, w->data);
            moveNext(B->alist[i]);
        }
    }
    return Y;
}

Matrix diff(Matrix A, Matrix B) {
    if (size(A) != size(B)) {
        fprintf(stderr, "diff Error: calling diff() precondition not met");
        exit(EXIT_FAILURE);
    }
    Matrix Y = newMatrix(size(A));
    if (A == B) {
        return Y;
    }
    for (int i = 1; i < size(A) + 1; i++) {
        moveFront(A->alist[i]);
        moveFront(B->alist[i]);
        while (index(A->alist[i]) >= 0 && index(B->alist[i]) >= 0) {
            Entry v = get(A->alist[i]);
            Entry w = get(B->alist[i]);
            if (v->cols > w->cols) {
                changeEntry(Y, i, w->cols, -w->data);
                moveNext(B->alist[i]);
            }
            else if (v->cols < w->cols) {
                changeEntry(Y, i, v->cols, v->data);
                moveNext(A->alist[i]);
            }
            else if ((v->cols == w->cols)) {
                changeEntry(Y, i, v->cols, (v->data - w->data));
                moveNext(A->alist[i]);
                moveNext(B->alist[i]);
            }
        }
        while (index(A->alist[i]) >= 0 && index(B->alist[i]) < 0) {
            Entry v = get(A->alist[i]);
            changeEntry(Y, i, v->cols, v->data);
            moveNext(A->alist[i]);
        }
        while (index(A->alist[i]) < 0 && index(B->alist[i]) >= 0) {
            Entry w = get(B->alist[i]);
            changeEntry(Y, i, w->cols, -w->data);
            moveNext(B->alist[i]);
        }
    }
    return Y;
}

double prohelper(List A, List B) {
    double total = 0;
    moveFront(A);
    moveFront(B);
    while (index(A) >= 0 && index(B) >= 0) {
        Entry E = get(A);
        Entry F = get(B);
        if (E->cols < F->cols) {
            moveNext(A);
            continue;
        }
        else if (E->cols > F->cols) {
            moveNext(B);
            continue;
        }
        if (E->cols == F->cols) {
            total += E->data * F->data;
            moveNext(A);
            moveNext(B);
        }
    }
    return total;
}

Matrix product(Matrix A, Matrix B) {
    if (size(A) != size(B)) {
        fprintf(stderr, "product Error: calling product() precondition not met");
        exit(EXIT_FAILURE);
    }
    double num = 0;
    Matrix Y = transpose(B);
    Matrix Z = newMatrix(size(A));
    for (int i = 1; i < size(A) + 1; i++) {
        if (length(A->alist[i]) == 0) {
            continue;
        }
        for (int k = 1; k < size(B) + 1; k++) {
            if (length(Y->alist[k]) == 0) {
                continue;
            }
            num = prohelper(A->alist[i], Y->alist[k]);
            if (num != 0) {
                changeEntry(Z, i, k, num);
            }
        }
    }
    return Z;
}

Matrix copy(Matrix A){
    Matrix Hello = newMatrix(size(A));
    for (int i = 1; i < size(A); i++) {
        moveFront(A->alist[i]);
        while(index(A->alist[i]) >= 0) {
            Entry E = (Entry) get(A->alist[i]);
            changeEntry(Hello, i, E->cols, E->data);
            moveNext(A->alist[i]);
        }
    }
    return Hello;
}


