#include <iostream>
#include <fstream>
#include "Deque.h"
using namespace std;

// Task 3
Deque create_deque() {
	// initialise deque members
	Deque deque;
	Iterator start;
	Iterator end;
	Node* normal_node_p = new Node;
	Node* sentinel_node_p = new Node;
	
	// initialise nodes
	normal_node_p->prev = sentinel_node_p;
	normal_node_p->next = sentinel_node_p;
	sentinel_node_p->prev = normal_node_p;
	sentinel_node_p->next = normal_node_p;
	
	// initialise iterators
	start.current = normal_node_p->arr;
	start.first = normal_node_p->arr;
	start.last = normal_node_p->arr + CHUNK_SIZE;
	start.node = normal_node_p;
	end = start;
	
	// initialise deque
	deque.start = start;
	deque.end = end;
	deque.sentinel = sentinel_node_p;
	deque.ll_size = 1;
	
	return deque;
}

void destroy_deque(Deque& deque) {
	// delete iterators
	deque.start.current = nullptr;
	deque.start.first = nullptr;
	deque.start.last = nullptr;
	deque.start.node = nullptr;
	deque.end.current = nullptr;
	deque.end.first = nullptr;
	deque.end.last = nullptr;
	deque.end.node = nullptr;
	
	// delete each node
	Node* node1_p = deque.sentinel->next;
	Node* node2_p;
	do {
		// store position of node after node1
		node2_p = node1_p->next;
		
		// delete node1
		node1_p->prev = nullptr;
		node1_p->next = nullptr;
		delete node1_p;
		
		node1_p = node2_p;
	} while (node2_p != deque.sentinel);
	node1_p = nullptr;
	node2_p = nullptr;
	
	// finally delete sentinel
	deque.sentinel->prev = nullptr;
	deque.sentinel->next = nullptr;
	delete deque.sentinel;
	deque.sentinel = nullptr;
	
	deque.ll_size = 0;
}

// Task 4
Iterator begin(const Deque& deque) {
	return deque.start;
}

Iterator end(const Deque& deque) {
	return deque.end;
}

int front(const Deque& deque) {
	if (empty(deque)) {
		cout << "Cannot get front: deque is empty" << endl;
		return -1;
	} else {
		return value(begin(deque));
	}
}

int back(const Deque& deque) {
	if (empty(deque)) {
		cout << "Cannot get back: deque is empty" << endl;
		return -1;
	} else {
		return value(prev(end(deque)));
	}
}

// Task 5
bool empty(const Deque& deque) {
	return equal(begin(deque), end(deque));
}

int size(const Deque& deque) {
	// Adds start node, middle nodes, end node
	return (deque.ll_size - 2) * CHUNK_SIZE + (deque.start.last - deque.start.current) + (deque.end.current - deque.end.first);
}

// Task 6
void push_back(Deque& deque, int val) {
	if (deque.end.current == deque.end.last) {
		// last item in node is filled
		if (deque.end.node->next == deque.sentinel) {
			// insert new node before sentinel
			Node* new_node = new Node;
			new_node->prev = deque.sentinel->prev;
			new_node->next = deque.sentinel;
			deque.sentinel->prev->next = new_node;
			deque.sentinel->prev = new_node;
			// increase link list size
			deque.ll_size++;
		}
		deque.end = next(deque.end);
		// point deque.end to first item in empty node
	}
	// point deque.end to empty position (last item + 1)
	*deque.end.current = val;
	deque.end.current++;
}

void push_front(Deque& deque, int val) {
	if (deque.start.current == deque.start.first) {
		// first item in node is filled
		if (deque.start.node->prev == deque.sentinel) {
			// insert new node after sentinel
			Node* new_node = new Node;
			new_node->prev = deque.sentinel;
			new_node->next = deque.sentinel->next;
			deque.sentinel->next->prev = new_node;
			deque.sentinel->next = new_node;
			// increase link list size
			deque.ll_size++;
		}
	}
	// point deque.start to item before first item
	deque.start = prev(deque.start);
	*deque.start.current = val;
}

void pop_back(Deque& deque) {
	if (empty(deque)) {
		cout << "Cannot pop_back: deque is empty" << endl;
	} else {
		deque.end = prev(deque.end);
		if (deque.end.current == deque.end.first && deque.ll_size != 1) {
			deque.end = prev(deque.end);
			deque.end.current++;
			// pop last node since it only has 1 item
			deque.sentinel->prev->next = nullptr;
			deque.sentinel->prev = deque.sentinel->prev->prev;
			deque.sentinel->prev->next->prev = nullptr;
			delete deque.sentinel->prev->next;
			deque.sentinel->prev->next = deque.sentinel;
			// decrease link list size
			deque.ll_size--;
		}
	}
}

void pop_front(Deque& deque) {
	if (empty(deque)) {
		cout << "Cannot pop_front: deque is empty" << endl;
	} else {
		if (deque.start.current == deque.start.last - 1) {
			if (deque.ll_size != 1) {
				deque.start = next(deque.start);
				// pop first node since it only has 1 item
				deque.sentinel->next->prev = nullptr;
				deque.sentinel->next = deque.sentinel->next->next;
				deque.sentinel->next->prev->next = nullptr;
				delete deque.sentinel->next->prev;
				deque.sentinel->next->prev = deque.sentinel;
				// decrease link list size
				deque.ll_size--;
			} else {
				// special case for popping last item in last node since start.current cannot be start.last, so we set both iterators to first item in node
				deque.start.current = deque.start.first;
				deque.end.current = deque.start.first; 
			}
		} else {
			deque.start.current++;
		}
	}
}

// Task 7
void print_detailed_deque(const Deque& deque) {
	// prints all nodes and items in array (there might be garbage values), as well as size of deque
	Node* node = deque.sentinel->next;
	cout << "[" << size(deque) << "] ";
	while (node != deque.sentinel) {
		// iterates through all items including items out of range
		if (node != deque.sentinel->next) {
			cout << ", ";
		}
		cout << "(" << node->arr[0];
		for (int i = 1; i < CHUNK_SIZE; i++) {
			cout << ", " << node->arr[i];
		}
		cout << ")";
		node = node->next;
	}
	cout << endl;
}

void print_deque(const Deque& deque) {
	if (empty(deque)) {
		cout << "[]" << endl;
	} else {
		// iterates through all items
		Iterator it = begin(deque);
		cout << "[";
		while (!equal(it, prev(end(deque)))) {
			cout << value(it) << ", ";
			it = next(it);
		}
		cout << back(deque) << "]" << endl;
	}
	// print_detailed_deque(deque);
}

// Task 8
void swap(int& a, int& b) {
	int temp = a;
	a = b;
	b = temp;
}

void insert(Deque& deque, const Iterator& pos, int val) {
	int previous_value = val;
	if (!empty(deque) && !equal(pos, end(deque)) ) {
		// iterates through all items from pos
		Iterator it = pos;
		while (!equal(it, prev(end(deque)))) {
			swap(previous_value, *(it.current));
			it = next(it);
		}
		swap(previous_value, *(it.current));
	}
	push_back(deque, previous_value);
}

void erase(Deque& deque, const Iterator& pos) {
	if (!empty(deque) && !equal(pos, end(deque)) ) {
		// iterates through all items until pos
		Iterator it = begin(deque);
		if (!equal(it, pos)) {
			int previous_value = value(it);
			it = next(it);
			while (!equal(it, pos)) {
				swap(previous_value, *(it.current));
				it = next(it);
			}
			swap(previous_value, *(it.current));
		}
		pop_front(deque);
	} else {
		cout << "Cannot erase: deque is empty" << endl;
	}
}

// Task 9
void store_deque(const Deque& deque, const char* filename) {
	ofstream file(filename);
	if (!empty(deque)) {
		// iterates through all items
		Iterator it = begin(deque);
		while (!equal(it, prev(end(deque)))) {
			file << value(it) << endl;
			it = next(it);
		}
		file << back(deque) << endl;
	}
	file.close();
}

Deque load_deque(const char* filename) {
	int val;
	ifstream file(filename);
	Deque deque = create_deque();
	while (file >> val) {
		push_back(deque, val);
	}
	
	return deque;
}

