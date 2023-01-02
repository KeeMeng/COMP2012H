struct Meaning{
	std::string meaning;
	std::string type;
};

class Node{
	Node* parent;
	Node* children[26];
public:
	Node();
	~Node();
	Meaning meaning;
	
	Node* operator[](const int& idx);
	void set_child(const int& idx, Node* ptr);
	Node*& get_parent();
};

class NodeStats{
	static int nodes_created;
	static int nodes_deleted;
	static int pointers_accessed;
public:
	static void print_statistics();
	static int get_nodes_created();
	static int get_nodes_deleted();
	static int get_pointers_accessed();
};

class Dictionary{
	Node* root;
	std::string name;

public:
	Dictionary(const std::string& name);
	~Dictionary();
	Dictionary(const Dictionary& d);
	Dictionary& operator=(const Dictionary& d);
	Dictionary(Dictionary&& d);
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
	
	void print_all_elements(std::ostream& o) const;
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
	
	Dictionary filter_starting_word(const char* key) const;
};
std::ostream& operator<<(std::ostream& o, Node* n);
std::ostream& operator<<(std::ostream& o, const Node& n);
std::ostream& operator<<(std::ostream& o, const Dictionary& dict);
