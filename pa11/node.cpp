#include <iostream>
#include "dictionary.h"

int NodeStats::nodes_created = 0;
int NodeStats::nodes_deleted = 0;
int NodeStats::pointers_accessed= 0;

int NodeStats::get_nodes_created() {
	return nodes_created;
}

int NodeStats::get_nodes_deleted() {
	return nodes_deleted;
}

int NodeStats::get_pointers_accessed() {
	return pointers_accessed;
}

void NodeStats::print_statistics(){
	std::cout << NodeStats::get_nodes_created() << "   " << NodeStats::get_nodes_deleted() << "\n";
}

Node::Node() {
	parent = nullptr;
	for (int i = 0; i < 26; i++){
		children[i] = nullptr;
	}
	NodeStats::nodes_created++;
}

Node::~Node() {
	for (int i = 0; i < 26; i++){
		if (children[i] != nullptr) {
			delete children[i];
		}
	}
	NodeStats::nodes_deleted++;
}

Node* Node::operator[](const int& idx) {
	NodeStats::pointers_accessed++;
	return children[idx];
}

void Node::set_child(const int& idx, Node* ptr) {
	children[idx] = ptr;
}

Node*& Node::get_parent() {
	return parent;
}

int Node::total_number_children() const{
	int total = 0;

	for (int i = 0; i < 26; i++){
		if (children[i] != nullptr) {
			total += (1 + children[i]->total_number_children());
		}
	}

	return total;
}