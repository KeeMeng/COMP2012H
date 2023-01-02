#ifndef PA5_DEQUE_DEQUE_ITERATOR_H
#define PA5_DEQUE_DEQUE_ITERATOR_H

const int CHUNK_SIZE = 8;   // the chunk size, i.e., size of array in each Node

struct Node {
    int arr[CHUNK_SIZE];        // the chunk
    Node* prev;                 // previous Node
    Node* next;                 // next Node
};

struct Iterator {
    int* current;           // current position
    int* first;             // begin of the chunk, i.e., the position of first item
    int* last;              // end of the chunk, i.e., the position after the last item
    const Node* node;       // current Node
};

void set_node(Iterator& it, Node* new_node);
Iterator next(const Iterator& it);
Iterator prev(const Iterator& it);
bool equal(const Iterator& it1, const Iterator& it2);
int value(const Iterator& it);

#endif //PA5_DEQUE_DEQUE_ITERATOR_H
