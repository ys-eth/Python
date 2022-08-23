/****************************************************************************************
*  Name: Yash Sharma
*  Cruz ID: yhsharma
*  Assignment Name: pa3
*****************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Graph.h"
#include "List.h"

typedef struct GraphObj {
    List *vertex;
    int *color;
    int *parent;
    int *discover;
    int *finish;
    bool xyz;
    int order;
    int size;
    int time;
} GraphObj;

/*** Constructors-Destructors ***/

Graph newGraph(int n) {
    Graph G = malloc(sizeof(GraphObj));
    G->vertex = malloc((n + 1) * sizeof(List));
    for (int i = 0; i < (n + 1); i++) {
        G->vertex[i] = newList();
    }

    G->color = malloc((n + 1) * sizeof(int));
    G->parent = malloc((n + 1) * sizeof(int));
    G->discover = malloc((n + 1) * sizeof(int));
    G->finish = malloc((n + 1) * sizeof(int));
    G->xyz = false;
    G->order = n;
    G->size = 0;
    G->time = 0;
    return G;
}

void freeGraph(Graph* pG) {
    for (int i = 0; i < (*pG)->order + 1; i++) {
        freeList(&(*pG)->vertex[i]);
    }
    free((*pG)->vertex);
    (*pG)->vertex = NULL;

    free((*pG)->color);
    (*pG)->color = NULL;
    
    free((*pG)->parent);
    (*pG)->parent = NULL;
    
    free((*pG)->discover);
    (*pG)->discover = NULL;
    
    free((*pG)->finish);
    (*pG)->finish = NULL;

    free(*pG);
    (*pG) = NULL;
}

/*** Access functions ***/

int getOrder(Graph G) {
    return G->order;
}

int getSize(Graph G) {
    return G->size;
}

int getParent(Graph G, int u) {
    if (getOrder(G) < u && u < 1) {
        fprintf(stderr, "getParent Error: calling getParent() precondition not met");
        exit(EXIT_FAILURE);
    }
    if (G->xyz == false) {
        return NIL;
    }
    return G->parent[u];
}

int getDiscover(Graph G, int u) {
    if (getOrder(G) < u && u < 1) {
        fprintf(stderr, "getDiscover Error: calling getDiscover() precondition not met");
        exit(EXIT_FAILURE);
    }
    if (G->xyz == false) {
        return UNDEF;
    }
    return G->discover[u];
}

int getFinish(Graph G, int u) {
    if (getOrder(G) < u && u < 1) {
        fprintf(stderr, "getFinish Error: calling getFinish() precondition not met");
        exit(EXIT_FAILURE);
    }
    if (G->xyz == false) {
        return UNDEF;
    }
    return G->finish[u];
}

/*** Manipulation procedures ***/

void insertionSort(Graph G, List L, int y) {
    moveFront(L);
    while (index(L) >= 0) {
        int x = get(L);
        if (x == y) {
            G->size--;
            return;
        }
        if (y < x) {
            insertBefore(L, y);
            return;
        }
        moveNext(L);
    }
    append(L, y);
}

void addEdge(Graph G, int u, int v) {
    if (getOrder(G) < u && u < 1) {
        fprintf(stderr, "addEdge Error: calling addEdge() precondition not met");
        exit(EXIT_FAILURE);
    }
    if (getOrder(G) < u && u < 1) {
        fprintf(stderr, "addEdge Error: calling addEdge() precondition not met");
        exit(EXIT_FAILURE);
    }

    addArc(G, u, v);
    addArc(G, v, u);
    G->size--;
}

void addArc(Graph G, int u, int v) {
    if (u < 1 || u > G->order || v < 1 || v > G->order) {
        fprintf(stderr, "addArc Error: calling addArc() precondition not met");
        exit(EXIT_FAILURE);
    }
    insertionSort(G, G->vertex[u], v);
    G->size++;
}

void Visit(Graph G, List L, int x) {
    G->discover[x] = ++(G->time);
    G->color[x] = GRAY;
    moveFront(G->vertex[x]);
    while (index(G->vertex[x]) >= 0) {
        int y = get(G->vertex[x]);
        if (G->color[y] == WHITE) {
            G->parent[y] = x;
            Visit(G, L, y);
        }
        moveNext(G->vertex[x]);
    }
    G->color[x] = BLACK;
    insertAfter(L, x);
    G->finish[x] = ++(G->time);
}

void DFS(Graph G, List S) {
    G->xyz = true;
    if (length(S) != getOrder(G)) {
        fprintf(stderr, "DFS Error: calling DFS() precondition not met");
        exit(EXIT_FAILURE);
    }
    for (int i = 1; i <= getOrder(G); i++) {
        G->color[i] = WHITE;
        G->parent[i] = NIL;
    }

    G->time = 0;
    moveBack(S);
    for (int i = 1; i <= getOrder(G); i++) {
        if (G->color[front(S)] == WHITE) {
            Visit(G, S, front(S));
        }
        deleteFront(S);
    }
}

/*** Other operations ***/

Graph transpose(Graph G) {
    Graph N = newGraph(G->order);
    for (int i = 1; i < G->order + 1; i++) {
        moveFront(G->vertex[i]);
        while (index(G->vertex[i]) >= 0) {
            int g = get(G->vertex[i]);
            addArc(N, g, i);
            moveNext(G->vertex[i]);
        }
    }
    return N;
}

Graph copyGraph(Graph G) {
    Graph M = newGraph(G->order);
    for (int i = 1; i < G->order + 1; i++) {
        M->vertex[i] = copyList(G->vertex[i]);
        M->color[i] = G->color[i];
        M->parent[i] = G->parent[i];
        M->discover[i] = G->discover[i];
        M->finish[i] = G->finish[i];
    }
    M->xyz = G->xyz;
    M->size = G->size;
    M->time = G->time;
    return M;
}

void printGraph(FILE* out, Graph G) {
    for (int i = 1; i < G->order + 1; i++) {
        fprintf(out, "%d: ", i);
        printList(out, G->vertex[i]);
        fprintf(out, "\n");
    }
}
