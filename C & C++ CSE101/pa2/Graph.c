/****************************************************************************************
*  Name: Yash Sharma
*  Cruz ID: yhsharma
*  Assignment Name: pa2
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
    int *distance;
    int source;
    int order;
    int size;
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
    G->distance = malloc((n + 1) * sizeof(int));
    G->source = NIL;
    G->order = n;
    G->size = 0;
    return G;
}

void freeGraph(Graph* pG) {
    for (int i = 0; i < (*pG)->order; i++) {
        freeList(&(*pG)->vertex[i]);
    }
    free((*pG)->color);
    (*pG)->color = NULL;
    
    free((*pG)->parent);
    (*pG)->parent = NULL;
    
    free((*pG)->distance);
    (*pG)->distance = NULL;
    
    free(pG);
    (*pG) = NULL;
}

/*** Access functions ***/

int getOrder(Graph G) {
    return G->order;
}

int getSize(Graph G) {
    return G->size;
}

int getSource(Graph G) {
    if (G->source == NIL) {
        return NIL;
    }
    return G->source;
}

int getParent(Graph G, int u) {
    if (getOrder(G) < u && u < 1) {
        fprintf(stderr, "getParent Error: calling getParent() precondition not met");
        exit(EXIT_FAILURE);
    }
    if (G->source == NIL) {
        return NIL;
    }
    return G->parent[u];
}

int getDist(Graph G, int u) {
    if (getOrder(G) < u && u < 1) {
        fprintf(stderr, "getDist Error: calling getDist() precondition not met");
        exit(EXIT_FAILURE);
    }
    if (G->source == NIL) {
        return INF;
    }
    return G->distance[u];
}

void getPath(List L, Graph G, int u) {
    if (getOrder(G) < u && u < 1) {    
        fprintf(stderr, "getPath Error: calling getPath() precondition not met");
        exit(EXIT_FAILURE);
    }
    if (G->source == NIL) {
        fprintf(stderr, "getPath Error: calling getPath() precondition not met");
        exit(EXIT_FAILURE);
    }
    if (G->distance[u] == INF) {
        append(L, NIL);
        return;
    }
    if (u == G->source) {
        append(L, u);
    }
    else if (G->parent[u] == NIL) {
        return;
    }
    else {
        getPath(L, G, G->parent[u]);
        append(L, u);
    }
}

/*** Manipulation procedures ***/

void makeNull(Graph G) {
    for (int i = 1; i < G->order; i++) {
        clear(G->vertex[i]);
    }
    G->size = 0;
    G->source = NIL;
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

void insertionSort(List L, int y) {
    moveFront(L);
    while (index(L) >= 0) {
        int x = get(L);
        if (y < x) {
            insertBefore(L, y);
            return;
        }
        moveNext(L);
    }
    append(L, y);
}

void addArc(Graph G, int u, int v) {
    if (u < 1 || u > G->order || v < 1 || v > G->order) {
        fprintf(stderr, "addArc Error: calling addArc() precondition not met");
        exit(EXIT_FAILURE);
    }
    insertionSort(G->vertex[u], v);
    G->size++;
}

void BFS(Graph G, int s) {
    for (int i = 0; i < G->order+1; i++) {
        G->color[i] = WHITE;
        G->distance[i] = INF;
        G->parent[i] = NIL;
    }
    G->color[s] = GRAY;
    G->distance[s] = 0;
    G->parent[s] = NIL;
    List Q = newList();
    append(Q, s);
    moveFront(Q);
    while (index(Q) >= 0) {
        int x = get(Q);
        moveFront(G->vertex[x]);
        while (index(G->vertex[x]) >= 0) {
            int y = get(G->vertex[x]);
            if (G->color[y] == WHITE) {
                G->color[y] = GRAY;
                G->distance[y] = G->distance[x] + 1;
                G->parent[y] = x;
                append(Q, y);
            }
            moveNext(G->vertex[x]);
        }
        G->color[x] = BLACK;
        moveNext(Q);
    }
    G->source = s;
    freeList(&Q);
}

/*** Other operations ***/

void printGraph(FILE* out, Graph G) {
    for (int i = 1; i < G->order; i++) {
        printf("%d: ", i);
        printList(out, G->vertex[i]);
        printf("\n");
    }
}
