#include <stdint.h>
#include <stdlib.h>
#include "node.h"
#include <stdio.h>

// Creates a node constructor that allows the user to create a node using a symbol and frequency
Node *node_create(uint8_t symbol, uint64_t frequency) {
    Node *node1 = malloc(sizeof(Node)); // Allocates memory on the heap
    node1->left = NULL; // sets the left node
    node1->right = NULL; // sets the right node
    node1->symbol = symbol; // sets the symbol node
    node1->frequency = frequency; // sets the frequency node
    return node1;
}

// deletes the node if called by the user using a valid node pointer
void node_delete(Node **n) {
    free(*n); // frees the value from the node
    *n = NULL; // sets the node to NULL
}

// Allows the user to join two child nodes of a parent node
Node *node_join(Node *left, Node *right) {
    Node *parent = node_create('$', left->frequency + right->frequency); // creates the parent node
    parent->left = left; // sets the left node
    parent->right = right; // sets the right node
    return parent; // returns the parent node: total of the left and right nodes
}

// Prints out the node when called by a user using a valid node pointer
void node_print(Node *n) {
    printf("%c %zu", n->symbol, n->frequency); // prints out the symbol and frequency of the node
}
