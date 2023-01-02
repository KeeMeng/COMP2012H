#include <vector>
#include <iostream>
#include <string>
#include "dictionary.h"
using namespace std;

// This function will not be used in any way. For C++, templates are usually defined in header files. However, for ZINC grading, we separate it into different files. So we need to use this 'trick' to instantiate the template.
void compiler_trick_useless_function() {
	Dictionary d{""};
	lambda_for_main_cpp ct;
	d.foreach(ct);
}

int Dictionary::character_to_index(const char& ch) {
	return (ch - 97);
}

char Dictionary::index_to_character(const int& idx) {
	return static_cast<char>(idx + 97);
}

const string& Dictionary::get_name() const {
	return name;
}

void Dictionary::set_name(const string& name_) {
	name = name_;
}

Dictionary::Dictionary(const string& name): name(name) {
	root = new Node();
}

Dictionary::~Dictionary() {
	delete root;
}

Dictionary::Dictionary(Dictionary&& d) {
	root = d.root;
	d.root = nullptr;
}

Dictionary& Dictionary::operator=(Dictionary&& d) {
	delete root;
	root = d.root;
	d.root = nullptr;
	return *this;
}

ostream& operator<<(ostream& o, Node* n) {
	o << (*n);
	return o;
}

ostream& operator<<(ostream& o, const Node& n) {
	o << " (" << n.meaning.type << ") " << n.meaning.meaning << " ";
	return o;
}

// TODO - Constructor for deep copy of dictionary.
Dictionary::Dictionary(const Dictionary& d) {
	root = nullptr;
	*this = d;
}

// TODO - Assignment operator for deep copy of dictionary.
Dictionary& Dictionary::operator=(const Dictionary& d) {
	if (this != &d) {
		delete root;
		root = new Node();
		vector<Node*> new_nodes { root };
		
		d.foreach([&new_nodes] (const Node* current_node, const vector<int> current_key) {
			// backtrack before adding new child node
			while (current_key.size() < new_nodes.size()) {
				new_nodes.pop_back();
			}
			// add node to dictionary
			Node* child_node = new Node();
			Node* parent_node = new_nodes.back();
			child_node->get_parent() = parent_node;
			parent_node->set_child(current_key.back(), child_node);
			child_node->meaning = current_node->meaning;
			// update vector
			new_nodes.push_back(child_node);
		});
	}
	return *this;
}

/**
 * TODO - Adds a node with the given key string, which is terminated with '\0'.
 * You should assume the key consists of lowercase letters only.
 * Do not delete the pointer.
*/
Node* Dictionary::add_node(const char* key) {
	Node* parent_node = root;
	for (int i = 0; key[i] != '\0'; i++) {
		Node* child_node = (*parent_node)[character_to_index(key[i])];
		// create node since it does not exists
		if (child_node == nullptr) {
			child_node = new Node();
			child_node->get_parent() = parent_node;
			parent_node->set_child(character_to_index(key[i]), child_node);
		}
		parent_node = child_node;
	}
	return parent_node;
}

// TODO - Shorthand for add_node.
Node* Dictionary::operator+=(const char* key) {
	return add_node(key);
}

/**
 * TODO - Removes all nodes starting with the given key string, which is terminated with '\0'.
 * You should assume the key consists of lowercase letters only.
 * Do not delete the pointer const char* key (of course you should clean up the nodes that are removed).
*/
void Dictionary::remove_node(const char* key) {
	Node* node = root;
	int i = 0;
	// traverse down tree to key
	for (; key[i] != '\0' && node != nullptr; node = (*node)[character_to_index(key[i++])]);
	if (node != nullptr && node != root) {
		node->get_parent()->set_child(character_to_index(key[i - 1]), nullptr);
	}
	delete node;
	if (node == root) {
		root = new Node();
	}
}

// TODO - Shorthand for remove_node.
void Dictionary::operator-=(const char* key) {
	remove_node(key);
}

/**
 * TODO - Finds a node with the given key string, which is terminated with '\0'.
 * Returns nullptr if no such node is found.
 * You should assume the key consists of lowercase letters only.
 * Do not delete the pointer.
*/
Node* Dictionary::find_node(const char* key) const {
	Node* node = root;
	for (int i = 0; key[i] != '\0' && node != nullptr; node = (*node)[character_to_index(key[i++])]);
	return node;
}

/**
 * TODO - A function to do pre-order traversal on the tree. The function accepts a lambda function as argument, and then the lambda function would be called for every node in the tree (except the root node). 
 * The lambda function accepts two arguments, (Node* current_node, vector<int>& current_key).
 * For each node accessed via pre-order traversal (except root node), call the lambda function.
 * Of course current_node should be the pointer to the node accessed. current_key should contain a list of integers which corresponds to the indices required to travel to current_node from the root node. For more explanation see the webpage.
 * The lambda is not supposed to change the dictionary.
*/
template<typename T>
void Dictionary::foreach(T&& lambda) const {
	vector<int> current_key;
	vector<Node*> nodes { root };
	for (int i = 0; i <= 26; i++) {
		if (i == 26) {
			if (nodes.back() == root) {
				// reached root, entire tree is traversed
				break;
			}
			// go back to parent node and find siblings
			nodes.pop_back();
			i = current_key.back();
			current_key.pop_back();
			continue;
		}
		Node* child_node = (*nodes.back())[i];
		if (child_node != nullptr) {
			// child node exists, call lambda
			current_key.push_back(i);
			nodes.push_back(child_node);
			lambda(nodes.back(), current_key);
			// start finding children of child_node (i will start at 0)
			i = -1;
		}
	}
}

// TODO - Prints all the nodes in the dictionary, in depth first alphabetical order.
void Dictionary::print_all_elements(ostream& o) const {
	int count = 1;
	
	foreach([&count, &o] (const Node* current_node, const vector<int> current_key) {
		for (int i = 0; i < (int)current_key.size(); o << index_to_character(current_key[i++]));
		o << *current_node << "[" << count++ << "]\n";
	});
}

// TODO - Calls print_all_elements
std::ostream& operator<<(std::ostream& o, const Dictionary& d) {
	d.print_all_elements(o);
	return o;
}

// TODO - Prints all the words in the dictionary, such that the word type is equal to the given type, in depth first alphabetical order
void Dictionary::print_elements_given_type(const char* type) const {
	int count = 1;
	
	foreach([&count, &type] (const Node* current_node, const vector<int> current_key) {
		if ((current_node->meaning.meaning != "") && (type == nullptr || current_node->meaning.type == type)) {
			for (int i = 0; i < (int)current_key.size(); cout << index_to_character(current_key[i++]));
			cout << *current_node << "[" << count++ << "]\n";
		}
	});
}

// TODO - Merges with another dictionary. Creates a new dictionary, and does not modify the contents of the original dictionaries. For words that exists in both dictionary, use the word definition in the dictionary this
Dictionary Dictionary::merge(const Dictionary& d2) const {
	Dictionary new_d(*this);
	new_d.set_name("");
		
	if (this != &d2) {
		d2.foreach([&new_d] (const Node* current_node, const vector<int> current_key) {
			// convert current_key to a char array
			string keys = "";
			for (int i = 0; i < (int)current_key.size(); keys += index_to_character(current_key[i++]));
			// add a new node if it does not exists, or find the node if it exists
			Node* new_node = new_d.add_node(keys.c_str());
			// use meaning from d2 only if not defined in this
			if (new_node->meaning.meaning == "") {
				new_node->meaning = current_node->meaning;
			}
		});
	}
	return new_d;
}

// TODO - Merges with another dictionary. Moves the contents of d2 into a new dictionary. For words that exists in both dictionary, use the word definition in the dictionary this
Dictionary Dictionary::merge(Dictionary&& d2) const {
	Dictionary new_d(move(d2));
	new_d.set_name("");
	vector<Node*> new_nodes { new_d.root };
	
	this->foreach([&new_nodes] (const Node* current_node, const vector<int> current_key) {
		// backtrack before adding new child node
		while (current_key.size() < new_nodes.size()) {
			new_nodes.pop_back();
		}
		Node* parent_node = new_nodes.back();
		Node* child_node = (*parent_node)[current_key.back()];
		if (child_node == nullptr) {
			// add node from this to new_d
			child_node = new Node();
			child_node->get_parent() = parent_node;
			parent_node->set_child(current_key.back(), child_node);
		}
		// replace meaning with definition from this
		if (current_node->meaning.meaning != "") {
			child_node->meaning = current_node->meaning;
		}
		new_nodes.push_back(child_node);
	});
	
	return new_d;
}

// TODO - Creates a new dictionary, consisting only of the words starting with the given key
Dictionary Dictionary::filter_starting_word(const char* key) const {
	Dictionary new_d("");
	if (key == nullptr || key[0] == '\0') {
		// deep copy if there is no filter
		new_d = *this;
	} else {
		foreach([&new_d, &key] (const Node* current_node, const vector<int> current_key) {
			// only add nodes if it is a word and starts with key
			if (current_node->meaning.meaning != "") {
				// check if current_node starts with key
				for (int i = 0; key[i] != '\0'; i++) {
					if (character_to_index(key[i]) != current_key[i]) {
						return;
					}
				}
				// convert current_key to a char array
				string keys = "";
				for (int i = 0; i < (int)current_key.size(); keys += index_to_character(current_key[i++]));
				
				// add node and meaning
				new_d.add_node(keys.c_str())->meaning = current_node->meaning;
			}
		});
	}
	return new_d;
}

Dictionary Dictionary::operator+(const Dictionary& d2) const {
	return merge(d2);
}

Dictionary Dictionary::operator+(Dictionary&& d2) const {
	return merge(move(d2));
}
