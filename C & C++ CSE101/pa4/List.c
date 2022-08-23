/****************************************************************************************
  *  Name: Yash Sharma
  *  Cruz ID: yhsharma
  *  Assignment Name: pa4
*****************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "List.h"
#include <string.h>
#include <assert.h>

typedef struct NodeObj* Node;

// Structure for Node Obj
typedef struct NodeObj {
    pointer data;
    Node next;
    Node prev;
} NodeObj;

// Structure for List Obj
typedef struct ListObj {
    Node front;
    Node back;
    Node cursor;
    int length;
    int cursorIndex;
} ListObj;

// Constructors - Destructors

// Creates a new node when called by the user
Node newNode(pointer v) {
    Node n = malloc(sizeof(NodeObj));
    assert(n != NULL);
    n->data = v;
    n->next = NULL;
    n->prev = NULL;
    return n;
}

// Deletes a node when used by the user
void nodeDelete(Node* N) {
    if (N != NULL) {
        free(*N);
        *N = NULL;
    }
}

// Utilized for creating a new List 
List newList(void) { // Creates and returns a new empty List.
    List L = malloc(sizeof(ListObj));
    assert(L != NULL);
    L->front = NULL;
    L->back = NULL;
    L->cursor = NULL;
    L->length = 0;
    L->cursorIndex = -1;
    return L;
}

// Frees any created List
void freeList(List* pL) { // Frees all heap memory associated with *pL, and sets *pL to NULL. 
    if (pL != NULL && *pL != NULL) {
        clear(*pL);
        free(*pL);
        *pL = NULL;
    }
}

// Returns the length of the List given in the parameters
int length(List L) {
    if (L == NULL) {
        fprintf(stderr, "Length Error: calling length() on NULL list reference");
        exit(EXIT_FAILURE);
    }
    return L->length;
}

// Returns the index of the List given in the parameters
int index(List L) {
    if (L->cursor == NULL) {
        return -1;
    }
    return L->cursorIndex;
}

// Returns the integer value of the Front given in List
pointer front(List L) {
    if (length(L) <= 0) {
        fprintf(stderr, "Front Error: calling front() on a empty list");
        exit(EXIT_FAILURE);
    }
    return L->front->data;
}


// Returns the integer value of the back given in List
pointer back(List L) {
    if (length(L) <= 0) {
        fprintf(stderr, "Back Error: calling back() on a empty list");
        exit(EXIT_FAILURE);
    }
    return L->back->data;
}

// Returns the list when called by user
pointer get(List L) {

    if (index(L) < 0) {
        fprintf(stderr, "Get Error: calling get() on a NULL cursor reference");
        exit(EXIT_FAILURE);
    }

    if (length(L) <= 0) {
        fprintf(stderr, "Get Error: calling get() on a empty list");
        exit(EXIT_FAILURE);
    }

    return L->cursor->data;
}

// Clears the List and resets the List to its original empty state.
void clear(List L) {
    while (length(L) > 0) {
         deleteFront(L);
    }
}

// Overwrites the cursor element's data with x
void set(List L, pointer x) {
    if (index(L) < 0) {
        fprintf(stderr, "Set Error: calling set() on a NULL cursor reference");
        exit(EXIT_FAILURE);
    }

    if (length(L) <= 0) {
        fprintf(stderr, "Set Error: calling set() on a empty list");
        exit(EXIT_FAILURE);
    }

    L->cursor->data = x;

}

// Sets cursor under the front element when the List is not empty
void moveFront(List L) {
    if (length(L) == 0) {
        return;
    }
    L->cursorIndex = 0;
    L->cursor = L->front;
}

// Sets cursor under the back element when the List is not empty
void moveBack(List L) {
    if (length(L) == 0) {
        return;
    }
    L->cursorIndex = length(L) - 1;
    L->cursor = L->back;
}

// Moves cursor to the previous node
void movePrev(List L) {
    if (L->cursor != NULL && L->cursor != L->front) {
        L->cursor = L->cursor->prev; 
        L->cursorIndex--;
        return;
    }

    if (L->cursor != NULL && L->cursor == L->front) {
        L->cursor = NULL;
        L->cursorIndex = -1;
        return;
    }
    return;
}

// Moves cursor to the next node
void moveNext(List L) {
    if (L->cursor != NULL && L->cursor != L->back) {
        L->cursor = L->cursor->next;
        L->cursorIndex++;
        return;
    }

    if (L->cursor != NULL && L->cursor == L->back) {
        L->cursor = NULL;
        L->cursorIndex = -1;
        return;
    }
    return;
}

// Inserts new element into L and inserts it before the front element.
void prepend(List L, pointer x) {
    if (length(L) == 0) {
        Node s = newNode(x);
        L->length += 1;
        L->front = s;
        L->back = s;
        return;
    }
    if (length(L) > 0) {
        Node s = newNode(x);
        L->length += 1;
    
        if (L->cursor != NULL) {
            L->cursorIndex += 1;
        }
        L->front->prev = s;
        s->next = L->front;
        L->front = s;
        return;
    }
}

// Inserts new element into L and inserts it after the back element.
void append(List L, pointer x) {
    if (length(L) == 0) {
        Node s = newNode(x);
        L->length += 1;
        L->front = s;
        L->back = s;
        return;
    }
    if (length(L) > 0) {
        Node s = newNode(x);
        L->length += 1;
        L->back->next = s;
        s->prev = L->back;
        L->back = s;
        return;
    }
}

// Inserts the new element before the cursor
void insertBefore(List L, pointer x) {
    if (index(L) < 0) {
        fprintf(stderr, "Insert Before Error: calling insertBefore() on a NULL cursor reference");
        exit(EXIT_FAILURE);
    }

    if (length(L) <= 0) {
        fprintf(stderr, "Insert Before Error: calling insertBefore() on a empty list");
        exit(EXIT_FAILURE);
    }
    if (index(L) == 0) {
        prepend(L, x);
        return;
    }
    Node t = newNode(x);
    t->next = L->cursor;
    t->prev = L->cursor->prev;
    L->cursor->prev = t;
    t->prev->next = t;
    L->length++;

    L->cursorIndex++;
    return;
}


// Inserts a new element after the cursor.
void insertAfter(List L, pointer x) {
    /*if (index(L) < 0) {
        fprintf(stderr, "Insert After Error: calling insertAfter() on a NULL cursor reference");
        exit(EXIT_FAILURE);
    }*/

    if (length(L) <= 0) {
        fprintf(stderr, "Insert After Error: calling insertAfter() on a empty list");
        exit(EXIT_FAILURE);
    }
    if (L->cursor == L->back) {
        append(L, x);
        return;
    }

    Node t = newNode(x);
    t->prev = L->cursor;
    t->next = L->cursor->next;
    L->cursor->next->prev = t;
    L->cursor->next = t;
    L->length++;

    return;
}

// Deletes the front element
void deleteFront(List L) {
    if (length(L) < 0) {
        fprintf(stderr, "Delete Front Error: calling deleteFront() on a NULL cursor reference");
        exit(EXIT_FAILURE);
    }
    if (L->front != NULL) {
        if (length(L) == 1) {
            nodeDelete(&L->front);
            L->length = 0;
            L->cursorIndex = -1;
            return;
        }
    if (length(L) > 1) {
        Node t = NULL;
        t = L->front;
        L->front = L->front->next;
        nodeDelete(&t);
        L->length--;
        if (L->cursor != NULL)  {
            if (L->cursor != L->front) {
                L->cursorIndex--;
            }
        else {
            L->cursorIndex = -1;
        }
    }
    return;
    }
    }
}

// Deletes the back element.
void deleteBack(List L) {
    if (length(L) < 0) {
        fprintf(stderr, "Delete Back Error: calling deleteBack() on a NULL cursor reference");
        exit(EXIT_FAILURE);
    }

    Node s = L->back;
    if (L->cursor == L->back) {
        L->cursorIndex = -1;
    }

    if (length(L) > 1) {
        L->back = L->back->prev;
    }
    else {
        L->back = NULL;
        L->front = NULL;
    }
    nodeDelete(&s);
    L->length--;

    /*if (length(L) == 1) {
        nodeDelete(&L->back);
        L->back = NULL;
        L->front = NULL;
        L->length = 0;
        L->cursorIndex = -1;
        return;
    }
    if (L->cursor == L->back) {
        puts("i am in the back");
        Node s = NULL;
        s = L->back;
        L->back = L->back->prev;
        printf("%d: \n", L->length);
        L->length--;
        printf("%d: \n", L->length);
        puts(" ");
        nodeDelete(&s);
        L->cursorIndex = -1;
        return;
    }
    L->back = L->back->prev;
    nodeDelete(&L->back->next);
    L->length--;
    */
}


// Deletes the cursor element, making cursor undefined.
void delete(List L) {
    if (L->cursor == L->front) {
        deleteFront(L);
        return;
    }
    if (L->cursor == L->back) {
        deleteBack(L);
        return;
    }
    Node deleteme = L->cursor;
    L->cursor->prev->next = L->cursor->next;
    L->cursor->next->prev = L->cursor->prev;
    L->length--;
    L->cursorIndex = -1;
    nodeDelete(&deleteme);
}

// Returns a new List representing the same integer sequence as L
List copyList(List L) {
    List M = newList();
    M->front = NULL;
    M->cursorIndex = -1;
    for (Node next = L->front; next != NULL; next = next->next) {
        append(M, next->data);
    }
    return M;
}

// Returns a new List which is the concatenation of A and B.
List concatList(List A, List B) {
    List L = copyList(A);
    for (Node next = B->front; next != NULL; next = next->next) {
        append(L, next->data);
    }
    return L;
}

