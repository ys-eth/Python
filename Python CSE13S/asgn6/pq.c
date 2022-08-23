#include "pq.h"
#include "node.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Create a struct for the PriorityQueue
struct PriorityQueue {
    uint32_t head;
    uint32_t tail;
    uint32_t capacity;
    Node **Q;
};

PriorityQueue *pq_create(uint32_t capacity) {
    PriorityQueue *pq = (PriorityQueue *) malloc(
        sizeof(PriorityQueue)); // Allocate memory on the heap for the priority queue using malloc
    if (pq) {
        pq->head = pq->tail = 0; // sets the head and tail equal to 0
        pq->capacity = capacity; // sets the capacity for the pq
        pq->Q = (Node **) calloc(capacity, sizeof(Node *)); // allocates memory for the Node *
        if (pq->Q) { // checks if the pq is the priority queue
            return pq;
        }
        free(pq);
    }
    return (PriorityQueue *) 0;
}

void pq_delete(PriorityQueue **q) { // frees the priority queue pointer pointing to the Node
    if (*q) {
        free((*q)->Q); // frees the pq pointer
        free(*q); // frees the pq
        *q = NULL; // sets the pq to null
    }
}

bool pq_empty(PriorityQueue *q) {
    return q->head == 0; // sets the head of the pq equal to 0
}

bool pq_full(PriorityQueue *q) {
    return q->head == q->capacity; // sets the head of the priority queue equal to the capacity
}

uint32_t pq_size(PriorityQueue *q) {
    return q->head; // Sets the head of the priority queue equal to the pointer
}

bool enqueue(PriorityQueue *q, Node *n) {
    bool full = pq_full(q);
    if (!full) { // checks if the queue is full
        if (pq_empty(q)) {
            q->Q[q->head] = n; // if so then add to the head of the queue
            q->head++;
            return true;
        } else {
            q->Q[q->head] = n;
            for (uint32_t i = 1; i < q->head;
                 i += 1) { //Checks the range between 1 and the len of array//
                uint32_t j = i;
                uint32_t temp
                    = q->Q[q->head]->frequency; //initializes and moves value to a temp variable//
                while (j > 0
                       && temp > q->Q[q->head - 1]
                                     ->frequency) { // checks for the frequency and iterates
                    q->Q[q->head] = q->Q[q->head - 1];
                    j -= 1; // subtracts from the temp var
                }
                q->Q[q->head]->frequency = temp; // moves stats and temp into the array j.//
            }
            q->head++; // adds to the head
            return true;
        }
    }
    return false;
}
bool dequeue(PriorityQueue *q, Node **n) {
    if (q) { //checks if the pq exists
        if (pq_empty(q)) { // if the pq is empty, then it will return false
            return false;
        }
        q->head--; // subtracts the header element in the priority queue order
        *n = q->Q[q->head];
        return true;
    }
    return false;
}

//debugging function that checks for errors and prints out the head, tail, and capacity.
void pq_print(PriorityQueue *q) {
    for (uint32_t i = 0; i < q->head; i++) {
        node_print(q->Q[i]);
    }
    printf("\nhead: %u\ntail: %u\ncapacity: %u\n", q->head, q->tail, q->capacity);
}
