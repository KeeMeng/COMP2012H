#ifndef PA5_DEQUE_DEQUE_H
#define PA5_DEQUE_DEQUE_H

#include "Deque_Iterator.h"
#include <iostream>
using namespace std;

struct Deque {
    Iterator start;     // the position of first item in deque
    Iterator end;       // the position after last item in deque

    Node* sentinel;     // sentinel of the circular doubly-linked list
    int ll_size;        // size of linked list, notice that this is number of chunks, not items
};

Deque create_deque();
void destroy_deque(Deque& deque);

Iterator begin(const Deque& deque);
Iterator end(const Deque& deque);
int front(const Deque& deque);
int back(const Deque& deque);

bool empty(const Deque& deque);
int size(const Deque& deque);

void push_back(Deque& deque, int val);
void push_front(Deque& deque, int val);
void pop_back(Deque& deque);
void pop_front(Deque& deque);

void print_deque(const Deque& deque);

void insert(Deque& deque, const Iterator& pos, int val);
void erase(Deque& deque, const Iterator& pos);

void store_deque(const Deque& deque, const char* filename);
Deque load_deque(const char* filename);

#endif //PA5_DEQUE_DEQUE_H
