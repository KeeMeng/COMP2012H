#include <iostream>
#include <fstream>
#include "Deque_Iterator.h"
using namespace std;

// Task 1
bool equal(const Iterator& it1, const Iterator& it2) {
	return (it1.current == it2.current);
}

int value(const Iterator& it) {
	return *(it.current);
}

// Task 2
void set_node(Iterator& it, Node* new_node) {
	it.node = new_node;
	it.first = new_node->arr;
	it.last = new_node->arr + CHUNK_SIZE;
}

Iterator next(const Iterator& it) {
	Iterator next_it = it;
	// bypass const pointer
	Node* location = it.node->prev->next;
	
	if (it.current >= it.last - 1) {
		// go to next node
		location = location->next;
		next_it.first = location->arr;
		next_it.last = location->arr + CHUNK_SIZE;
		next_it.current = next_it.first;
		next_it.node = location;
	} else {
		// go to next item
		next_it.current = it.current + 1;
	}
	
	return next_it;
}

Iterator prev(const Iterator& it) {
	Iterator prev_it = it;
	// bypass const pointer
	Node* location = it.node->prev->next;
	
	if (it.current <= it.first) {
		// go to prev node
		location = location->prev;
		prev_it.first = location->arr;
		prev_it.last = location->arr + CHUNK_SIZE;
		prev_it.current = prev_it.last - 1;
		prev_it.node = location;
	} else {
		// go to prev item
		prev_it.current = it.current - 1;
	}
	
	return prev_it;
}
