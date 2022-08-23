#include <stdint.h>
#include <stdlib.h>
#include "node.h"
#include <stdio.h>
#include <string.h>

Node *node_create(char *word) {
    Node *node1 = malloc(sizeof(Node)); // Allocates memory on the heap
    if (node1 != NULL) { // if the node exists
        node1->word = strdup(word); // return the pointer to the word string
        node1->count = 0; // initializes the count
        return node1; //returns the node
    }
    return node1;
}

void node_delete(Node **n) {
    free((*n)->word); // free the pointer of the node to word
    ((*n)->word) = NULL; // set the pointer to null
    free(*n); // free the node
    *n = NULL; // set the node equal to null
}

void node_print(Node *n) {
    printf("%s %u\n", n->word, n->count); // prints out the word and count
}
