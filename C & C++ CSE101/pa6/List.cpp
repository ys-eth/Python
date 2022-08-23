/****************************************************************************************
  *  Name: Yash Sharma
  *  Cruz ID: yhsharma
  *  Assignment Name: pa6
  *  Code referenced from Queue.cpp
*****************************************************************************************/

#include <iostream>
#include <string>
#include <cassert>
#include <stdexcept>
#include "List.h"
#define NEG -223

// Private Constructor

List::Node::Node(ListElement x) {
    data = x;
    next = nullptr;
    prev = nullptr;
}

// Class Constructors & Destructors

// Creates a new List in the empty state

List::List() {
    frontDummy = new Node(NEG);
    backDummy = new Node(NEG);
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    pos_cursor = 0;
    num_elements = 0;
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
}

List::List(const List &L) {
    frontDummy = new Node(NEG);
    backDummy = new Node(NEG);
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    pos_cursor = 0;
    num_elements = 0;
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    Node* N = L.frontDummy->next;
    while (N != L.backDummy) {
        insertBefore(N->data);
        N = N->next;
    }
}

// Destructors

List::~List() {
    clear();
    delete frontDummy;
    delete backDummy;
}

// Access Functions

int List::length() const {
    return num_elements;
}

ListElement List::front() const {
    if (!(length() > 0)) {
        throw std::length_error("List: front(): empty list");
    }
    return frontDummy->next->data;
}

ListElement List::back() const {
    if (!(length() > 0)) {
        throw std::length_error("List: back(): empty list");
    }
    return backDummy->prev->data;
}

int List::position() const {
    return pos_cursor;
}

ListElement List::peekNext() const {
    if (position() >= length()) {
        throw std::range_error("List: peekNext(): cursor at back");
    }
    return afterCursor->data;
}

ListElement List::peekPrev() const {
    if (!(position() > 0)) {
        throw std::range_error("List: peekPrev(): cursor at front");
    }
    return beforeCursor->data;
}

// Manipulation procedures

void List::clear() {
    moveFront();
    while (length() > 0) {
        eraseAfter();
    }
    num_elements = 0;
    pos_cursor = 0;
}

void List::moveFront() {
    pos_cursor = 0;
    beforeCursor = frontDummy;
    afterCursor = frontDummy->next;
}

void List::moveBack() {
    pos_cursor = length();
    beforeCursor = backDummy->prev;
    afterCursor = backDummy;
}

ListElement List::moveNext() {
    if (!(length() > position())) {
        throw std::range_error("List: moveNext(): cursor at back");
    }
    pos_cursor++;
    beforeCursor = beforeCursor->next;
    afterCursor = afterCursor->next;
    return beforeCursor->data;
}

ListElement List::movePrev() {
    if (!(position() > 0)) {
        throw std::range_error("List: movePrev(): cursor at front");
    }
    pos_cursor--;
    beforeCursor = beforeCursor->prev;
    afterCursor = afterCursor->prev;
    return afterCursor->data;
}

void List::insertAfter(ListElement x) {
    Node* newNode = new Node(x);
    newNode->prev = beforeCursor;
    newNode->next = afterCursor;
    afterCursor->prev = newNode;
    beforeCursor->next = newNode;
    afterCursor = newNode;
    num_elements++;
}

void List::insertBefore(ListElement x) {
    Node* newNode = new Node(x);
    newNode->next = afterCursor;
    newNode->prev = beforeCursor;
    afterCursor->prev = newNode;
    beforeCursor->next = newNode;
    beforeCursor = newNode;
    pos_cursor++;
    num_elements++;
}

void List::setAfter(ListElement x) {
    if (!(length() > position())) {
        throw std::range_error("List: setAfter(): cursor at back");
    }
    afterCursor->data = x;
}

void List::setBefore(ListElement x) {
    if (!(position() > 0)) {
        throw std::range_error("List: setBefore(): cursor at front");
    }
    beforeCursor->data = x;
}

void List::eraseAfter() {
    if (!(length() > position())) {
        throw std::range_error("List: eraseAfter(): cursor at back");
    }
    Node* newNode = afterCursor;
    afterCursor = afterCursor->next;
    beforeCursor->next = afterCursor;
    afterCursor->prev = beforeCursor;
    num_elements--;
    delete(newNode);
}

void List::eraseBefore() {
    if (!(position() > 0)) {
        throw std::range_error("List: eraseBefore(): cursor at front");
    }
    Node* newNode = beforeCursor;
    beforeCursor = beforeCursor->prev;
    beforeCursor->next = afterCursor;
    afterCursor->prev = beforeCursor;
    num_elements--;
    pos_cursor--;
    delete(newNode);
}

// Other Functions

int List::findNext(ListElement x) {
    while (afterCursor->next != backDummy) {
        if (afterCursor->data == x) {
            moveNext();
            return position();
        }
        moveNext();
    }
    moveBack();
    return -1;
}

int List::findPrev(ListElement x) {
    while (beforeCursor->prev != frontDummy) {
        if (beforeCursor->data == x) {
            movePrev();
            return position();
        }
        movePrev();
    }
    moveFront();
    return -1;
}

void List::cleanup() {

}
    
List List::concat(const List& L) const {
    List A;
    Node *B = frontDummy->next;
    Node *C = L.frontDummy->next;

    while (B != backDummy) {
        A.insertAfter(B->data);
        B = B->next;
    }

    while (C != L.backDummy) {
        A.insertAfter(C->data);
        C = C->next;
    }

    A.moveFront();
    return A;
}

std::string List::to_string() const {
    Node* N = nullptr;
    std::string s = "(";

    for (N = frontDummy->next; N->next != nullptr; N = N->next) {
        s += std::to_string(N->data) + "";
        if (N->next != backDummy) {
            s += ", ";
        }
    }
    s += ")";
    return s;
}

bool List::equals(const List& R) const {
    bool equal = false;
    Node* N = nullptr;
    Node* M = nullptr;
    
    equal = (this->length() == R.length());
    N = this->frontDummy->next;
    M = R.frontDummy->next;
    while (equal && N != backDummy) {
        equal = (N->data == M->data);
        N = N->next;
        M = M->next;
    }
    return equal;
}

// Overriden Operators

std::ostream& operator<<(std::ostream& stream, const List& L) {
    return stream << L.List::to_string();
}

bool operator==(const List& A, const List& B) {
    return A.List::equals(B);
}

List& List::operator=(const List& L) {
    if (this != &L) {
        List temp = L;
        std::swap(frontDummy, temp.frontDummy);
        std::swap(backDummy, temp.frontDummy);
        std::swap(beforeCursor, temp.beforeCursor);
        std::swap(afterCursor, temp.afterCursor);
        std::swap(num_elements, temp.num_elements);
        std::swap(pos_cursor, temp.pos_cursor);
    }
    return *this;
}

