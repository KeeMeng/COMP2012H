#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <string>
#include <vector>

class Dictionary;

class Tasks;

/**
 * TODO - operator overloading for cout and add node and remove node.
 * website 'Efficiency' change to 'Efficient implementation of tree traversal'
 * website image of sample dictionary update to real words
 * add const to filter dictionary
 * */

struct Meaning{
	std::string meaning;
	std::string type;
};

class Node{
	Node* parent;
	Node* children[26];
	// this is for internal automatic grading in ZINC. it is normal that you cannot access this function.
	int total_number_children() const;

	public:
		Node();
		~Node();
		Meaning meaning;
		
		/**
		 * For good practice, the parent and children pointers should be accessible only to Dictionary (using friend).
		 * In our case, the children pointers should be inaccessible, but the function operator[] should be, as the
		 * pointers_accessed increments by 1 in each access. There is no way specify which members to be exposed to the
		 * friend, so the pointers are chosen to be exposed in this case.
		*/
		
		// Access the pointers to the children. Increments the pointers_accessed value by 1.
		Node* operator[](const int& idx);
		// Shorthand for "children[idx] = ptr". Does not increment pointers_accessed, or delete any pointers.
		void set_child(const int& idx, Node* ptr);
		// Returns the reference to the parent pointer. Does not increment pointers_accessed.
		Node*& get_parent();
		
		// For internal ZINC grading
		friend Tasks;
};

class NodeStats{
	static int nodes_created;
	static int nodes_deleted;
	static int pointers_accessed;
	friend Node;
	
	public:
		static void print_statistics();
		
		static int get_nodes_created();
		static int get_nodes_deleted();
		static int get_pointers_accessed();
};

class lambda_for_main_cpp{
	public:
		int count;
		void operator()(Node* current_node, std::vector<int>& current_key);
};

class Dictionary{
	Node* root;
	std::string name;

	public:
		Dictionary(const std::string& name);
		~Dictionary();
		/**
		 * Deep copy
		*/
		Dictionary(const Dictionary& d);
		/**
		 * Deep copy
		*/
		Dictionary& operator=(const Dictionary& d);
		/**
		 * Move
		*/
		Dictionary(Dictionary&& d);
		/**
		 * Move
		*/
		Dictionary& operator=(Dictionary&& d);
		
		static int character_to_index(const char& ch);
		static char index_to_character(const int& i);
		
		Node* find_node(const char* key) const;
		Node* add_node(const char* key);
		void remove_node(const char* key);
		Node* operator+=(const char* key);
		void operator-=(const char* key);
		
		const std::string& get_name() const;
		void set_name(const std::string& name);
		
		/**
		 * A function to do pre-order traversal on the tree. The function accepts a lambda function as argument,
		 * and then the lambda function would be called for every node in the tree (except the root node). 
		 * The lambda function accepts two arguments, (Node* current_node, vector<int>& current_key).
		 * For each node accessed via pre-order traversal (except root node), call the lambda function.
		 * 
		 * Of course current_node should be the pointer to the node accessed. current_key should contain
		 * a list of integers which corresponds to the indices required to travel to current_node from
		 * the root node.
		*/
		template<typename T> void foreach(T&& lambda) const;
		
		/**
		 * Prints all elements to console.
		*/
		void print_all_elements(std::ostream& o) const;
		
		/**
		 * Prints all elements given a type. If type == nullptr then all types are accepted.
		*/
		void print_elements_given_type(const char* type) const;
		
		/**
		 * Creates a new dictionary by merging the contents with both dictionaries.
		 * Does not change the contents of 'this' and 'd2'. 
		 * If a word definition exists in both dictionaries, the new dictionary would
		 * use the word definition in 'this'.
		*/
		Dictionary merge(const Dictionary& d2) const;
		
		/**
		 * Creates a new dictionary by merging the contents with both dictionaries.
		 * This first moves the contents of d2 into the new dictionary, and then
		 * appending the contents of 'this'. 
		 * 
		 * In details, the root node of d2 should be set to nullptr and it is not
		 * necessary to deep copy the contents of d2.
		*/
		Dictionary merge(Dictionary&& d2) const;
		
		Dictionary operator+(const Dictionary& d2) const;
		Dictionary operator+(Dictionary&& d2) const;
		
		/**
		 * Returns a new dictionary consisting only of words starting with the given key.
		 * If no such words / nodes exists, return an empty dictionary.
		*/
		Dictionary filter_starting_word(const char* key) const;
		
		// For internal ZINC grading
		friend Tasks;
};

/**
 * Calls the operator below
*/
std::ostream& operator<<(std::ostream& o, Node* n);
/**
 * Outputs the contents of a node to the console. For the format, see the webpage
*/
std::ostream& operator<<(std::ostream& o, const Node& n);

/**
 * Basically just call print_all_elements.
*/
std::ostream& operator<<(std::ostream& o, const Dictionary& dict);

#endif