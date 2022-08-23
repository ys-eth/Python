/****************************************************************************************
*  Name: Yash Sharma
*  Cruz ID: yhsharma
*  Assignment Name: pa3
****************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "List.h"
#include "Graph.h"

int main(int argc, char* argv[]){
   
    int m = 6;
    List A = newList();
    Graph B = newGraph(m);
    Graph C = NULL;
    Graph D = NULL;

    for (int x = 1; x <= m; x++) {
        append(A, x);
    }

    addArc(B, 1, 3);
    addArc(B, 1, 4);
    addArc(B, 2, 3);
    addArc(B, 2, 5);
    addArc(B, 3, 3);
    addArc(B, 3, 5);
    addArc(B, 3, 6);
    addArc(B, 4, 1);
    addArc(B, 4, 5);
    addArc(B, 5, 2);
    addArc(B, 5, 5);
    addArc(B, 6, 4);
    printGraph(stdout, B);

    DFS(B, A);
    fprintf(stdout, "\n");
    fprintf(stdout, "x: discover finish parent\n");
    for (int x = 1; x <= m; x++) {
        fprintf(stdout, "%d: %2d %2d %2d\n", x, getDiscover(B, x), getFinish(B, x), getParent(B, x));
    }
    fprintf(stdout, "\n");
    printList(stdout, A);
    fprintf(stdout, "\n");

    C = transpose(B);
    D = copyGraph(B);
    fprintf(stdout, "\n");
    printGraph(stdout, D);
    fprintf(stdout, "\n");
    printGraph(stdout, C);
    fprintf(stdout, "\n");

    DFS(C, A);
    
    fprintf(stdout, "\n");
    fprintf(stdout, "x: discover finish parent\n");
    for (int x = 1; x <= m; x++) {
        fprintf(stdout, "%d: %2d %2d %2d\n", x, getDiscover(C, x), getFinish(C, x), getParent(C, x));
    }
    fprintf(stdout, "\n");
    printList(stdout, A);
    fprintf(stdout, "\n");
    freeList(&A);
    freeGraph(&B);
    freeGraph(&C);
    freeGraph(&D);
    return(0);
}
