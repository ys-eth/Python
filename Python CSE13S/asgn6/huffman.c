#include "node.h"
#include "code.h"
#include "pq.h"
#include "io.h"
#include "stack.h"
#include "huffman.h"
#include "defines.h"
#include <stdlib.h>
#include <stdint.h>

Node *build_tree(uint64_t hist[static ALPHABET]) {
    //create pq from histogram
    PriorityQueue *pq
        = pq_create(ALPHABET); // creates a priority queue with alphabet as the histogram
    for (
        int index = 0; index < ALPHABET;
        index++) { // loops through an index and checks if the characters are greater than the index. Increments index as well
        Node *n = node_create(index, hist[index]); // creates a node with index and histogram
        enqueue(pq, n); // enqueues the node created from pq
    }

    Node *left = NULL; // sets the left node
    Node *right = NULL; // sets the right node
    Node *top = NULL; // sets the top node
    Node *root = NULL; // sets the root

    while (pq_size(pq)
           > 1) { // loops through the size of the while loop while pq_size is greater than 1
        dequeue(pq, &left); // dequeues the pq and the left node
        dequeue(pq, &right); // dequeues the right node from the pq
        top = node_join(left, right); // joins the two child nodes into one parent node: top
        enqueue(pq, top); // enqueues the parent node from the pq
    }
    dequeue(pq, &root); // dequeues the root from the pq
    return root;
}

void build_codes(Node *root, Code table[static ALPHABET]) {

    Code c = code_init(); // initializes the code

    if (root != NULL) { // checks if the root exists
        if (!(root->left) & !(root->right)) { // if the left node and right node exists
            table[ALPHABET] = c; // set the table alphabet equal to the code
        } else {
            code_push_bit(&c, 0); // push the code bit
            build_codes(root->left, &table[ALPHABET]); // builds the code for left root and table
            code_pop_bit(&c, 0); //pops the bit for the code

            code_push_bit(&c, 1); // pushes the bit for the code
            build_codes(
                root->right, &table[ALPHABET]); // builds the code for the right root and the table
            code_pop_bit(&c, 0); // pops the bit for the code
        }
    }
}

void dump_tree(int outfile, Node *root) {

    uint8_t L = 'L'; // initializes the character L
    uint8_t I = 'I'; // initializes the character I

    if (root) { // if the root exists
        dump_tree(outfile, root->left); // dump the left node
        dump_tree(outfile, root->right); // dump the right node

        if (!(root->left) & !(root->right)) { // if the right & left node exist
            write_bytes(outfile, &L, 1); // write the left one
            uint8_t sym = root->symbol; // set the symbol for the Node
            write_bytes(outfile, &sym, 1); // write the symbol to the outfile
        } else {
            write_bytes(outfile, &I, 1); // write the I character to the outfile
        }
    }
}

Node *rebuild_tree(uint16_t nbytes, uint8_t tree[static nbytes]) {
    Node *left = NULL;
    Node *right = NULL;
    Node *top = NULL;
    Node *root = NULL;
    Stack *s = stack_create(nbytes); // creates a new stack with nbytes

    for (
        uint16_t i = 0; i < nbytes;
        nbytes++) { // loops through the nybtes and increments it whenever the nbytes are greater than the iterator
        if (tree[i]
            == 'L') { // if the index of the tree is equal to the character of L, create a node and push it to the stack
            Node *n1 = node_create(tree[i + 1], 0);
            stack_push(s, n1);
        }
        if (tree[i]
            == 'I') { // if the index of the tree is equal to the character of I, pop the left and right bits off the stack and join them in a parent node. then push them onto the stack
            stack_pop(s, &right);
            stack_pop(s, &left);
            top = node_join(left, right);
            stack_push(s, top);
        }
    }
    stack_pop(s, (&(root))); // pop the remaining node root
    return root;
}

void delete_tree(Node **root) {
    if (&(*root)) { // if the root pointer exists
        delete_tree(&(*root)->left); // delete the left node
        delete_tree(&(*root)->right); // delete the right node
        if (root) {
            if (!((*root)->left) & !((*root)->right)) { // if the left node and the right node exist
                node_delete(&(*root)); // delete the root
            }
        }
    }
}
