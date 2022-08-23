#include "node.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "stack.h"
#include <stdlib.h>

struct Stack { // creates a struct for Stack and initialize variables for top, capacity, and a Node
    uint32_t top;
    uint32_t capacity;
    Node **items;
};

Stack *stack_create(uint32_t capacity) {
    Stack *stack1 = (Stack *) malloc(sizeof(Stack)); // allocates memory on the heap for a Stack
    if (stack1 != NULL) { // checks if the stack is existent
        stack1->top = 0; // adds the stack pointer to top
        stack1->capacity = capacity; // adds the pointer to capacity
        stack1->items
            = (Node **) malloc(stack1->capacity * sizeof(Node *)); //allocates memory on the heap
        if (stack1->items == NULL) { // checks if stack pointer of items is NULL
            free(stack1); // frees the stack variable
            stack1 = NULL; // sets the stack equal to NULL
        }
    }
    return stack1; // returns stack
}

void stack_delete(Stack **s) {
    free((*s)->items); //Frees the pointer stack and points it to items
    (*s)->items = NULL; // Sets the stack pointer to null
    free(*s); // Frees stack pointer
    *s = NULL; // Sets stack pointer equal to null
}

bool stack_empty(Stack *s) {
    return s->top == 0; // Set top of stack equal to 0
}

bool stack_full(Stack *s) {
    return s->top == s->capacity; // Set the top of stack equal to capacity
}

uint32_t stack_size(Stack *s) {
    return s->top; // Sets the top of stack
}

bool stack_push(Stack *s, Node *n) {
    if (stack_full(s)) { // Checks if the stack is full
        return false;
    }
    s->items[s->top] = n; // adds the items to the top of the stack
    s->top += 1; // increments the top
    return true;
}

bool stack_pop(Stack *s, Node **n) {
    if (stack_empty(s)) { // checks if the stack is empty
        return false;
    }
    s->top -= 1; // decrements from the top
    *n = s->items[s->top]; // adds the items to the top of the node
    return true;
}
void stack_print(Stack *s) { // Debugging function that prints out the top and capacity of the stack
    printf("\ntop: %u\ncapacity: %u\n", s->top, s->capacity);
}
