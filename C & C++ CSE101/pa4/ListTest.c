/****************************************************************************************
  *  Name: Yash Sharma
  *  Cruz ID: yhsharma
  *  Assignment Name: pa4
*****************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "List.h"

int main(void) {
    printf("New List Test Case\n");
    List T = newList();
    if (T != NULL) {
        printf("Success\n");
    }
    else {
        printf("Failure\n");
    }

    printf("Append and Prepend Test Cases\n");
    
    int x1 = 2;
    int x2 = 3;
    int x3 = 6;
    int x4 = 4;
    append(T, x1);
    append(T, x2);
    prepend(T, x3);
    prepend(T, x4);

    printf("List: ");
    printList(stdout, T);
    
    List B = newList();
    append(B, x1);
    append(B, x2);
    prepend(B, x3);
    prepend(B, x4);
    printList(stdout, B);
    printf("Length of List T: %d\n", length(T));
    printf("Index Test: %d\n", index(T));
    printf("Front Test: %d\n", front(T));
    printf("Back Test: %d\n", back(T));
    
    moveFront(T);
    printf("Get Test: %d\n", get(T));
    
    if (index(T) == 0) {
        printf("Success!\n");
    }
    else {
        printf("Failure\n");
    }

    if (equals(B, T) != false) {
        printf("Success\n");
    }
    else {
        printf("Failure\n");
    }

    printf("List: ");
    clear(B);
    printList(stdout, B);
    set(T, 2);
    if (get(T) == 2) {
        printf("Success, this is the correct number! %d\n", get(T));
    }
    moveBack(T);
    if (index(T) == length(T) - 1) {
        printf("Success\n");
    }
    else {
        printf("Failure\n");
    }

    printf("Index Test: %d\n", index(T));
    movePrev(T);
    printf("Index after moving previous value: %d\n", index(T));
    printf("Index before moving previous value: %d\n", index(T));
    moveNext(T);
    printf("Index after moving next value: %d\n", index(T));

    printList(stdout, T);
    insertBefore(T, 8);
    printList(stdout, T);
    insertAfter(T, 7);
    printList(stdout, T);
    printf("Delete Test Cases\n");
    printList(stdout, T);
    printf("deleteFront Test Case\n");
    deleteFront(T);
    printList(stdout, T);
    printf("deleteBack Test Case\n");
    deleteBack(T);
    printList(stdout, T);

    printf("Delete Test Case: %d\n", get(T));
    delete(T);
    printList(stdout, T);
    return 0;
}
