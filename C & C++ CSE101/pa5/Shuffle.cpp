 /****************************************************************************************
# *  Name: Yash Sharma
# *  Cruz ID: yhsharma
# *  Assignment Name: pa5
# *****************************************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include "List.h"

void shuffle(List& E){
    List A;
    List B;
    List C;
    C.moveFront();
    for (int i = 0; i < (E.length() / 2); i++){
        A.insertBefore(E.peekNext());
        E.moveNext();
    }
    for (int j = (E.length() / 2) ; j < E.length(); j++){
        B.insertBefore(E.peekNext());
        E.moveNext();
    }
    A.moveFront();
    B.moveFront();

    while (C.length() != E.length()){
        if (A.position() != A.length()){
            C.insertBefore(A.peekNext());
            A.moveNext();
        }
        if (B.position() != B.length()){
            C.insertBefore(B.peekNext());
            B.moveNext();
        }
    }
    E = C;
}


int main(int argc, char * argv[]) {
    return (EXIT_SUCCESS);
}
