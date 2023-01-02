using namespace std;

template <typename K, typename V>
Skiplist<K, V>::Node::Node() {
	nexts = new Node*[1];
	nexts[0] = nullptr;
	levels = 1;
}

template <typename K, typename V>
Skiplist<K, V>::Node::Node(K key_, V value_, int levels_) {
	nexts = new Node*[levels_];
	for (int i = 0; i < levels_; i++) {
		nexts[i] = nullptr;
	}
	key = key_;
	value = value_;
	levels = levels_;
}

template <typename K, typename V>
Skiplist<K, V>::Node::~Node() {
	for (int i = 0; i < levels; i++) {
		nexts[i] = nullptr;
	}
	delete [] nexts;
}

template <typename K, typename V>
Skiplist<K, V>::Skiplist(double prob_) {
	head = new Node();
	prob = prob_;
}

template <typename K, typename V>
Skiplist<K, V>::~Skiplist() {
	Node* node = head;
	Node* next_node = head;
	while (node != nullptr) {
		next_node = node->nexts[0];
		delete node;
		node = next_node;
	}
}

template <typename K, typename V>
Skiplist<K, V>& Skiplist<K, V>::operator=(const Skiplist<K, V>& other) {
	// avoid self assignment
	if (this != &other) {
		// delete previous skiplist
		if (this->head != nullptr) {
			Node* node = this->head;
			Node* next_node = this->head;
			while (node != nullptr) {
				next_node = node->nexts[0];
				delete node;
				node = next_node;
			}
		}
		// initialise variables and create sentinel node
		this->prob = other.prob;
		this->head = new Node();
		this->head->levels = other.head->levels;
		delete [] this->head->nexts;
		this->head->nexts = new Node*[other.head->levels];
		
		// temporary arrays to store the previous node on the same level and its data
		Node** level_nodes = new Node*[other.head->levels];
		Node** new_level_nodes = new Node*[other.head->levels];
		
		for (int i = 0; i < other.head->levels; i++) {
			new_level_nodes[i] = this->head;
			level_nodes[i] = other.head->nexts[i];
			this->head->nexts[i] = nullptr;
		}
		
		// iterate through nodes
		Node* new_node = this->head;
		for (Node* node = other.head->nexts[0]; node != nullptr; node = node->nexts[0]) {
			// create new node
			new_node->nexts[0] = new Node(node->key, node->value, node->levels);
			new_node = new_node->nexts[0];
			
			// update level nodes arrays
			for (int i = 0; i < node->levels; i++) {
				if (level_nodes[i] == node) {
					new_level_nodes[i]->nexts[i] = new_node;
					new_level_nodes[i] = new_level_nodes[i]->nexts[i];
					level_nodes[i] = level_nodes[i]->nexts[i];
				}
			}
		}
		
		for (int i = 0; i < new_node->levels; i++) {
			if (level_nodes[i] == nullptr) {
				new_level_nodes[i]->nexts[i] = nullptr;
			}
		}
		
		delete [] level_nodes;
		delete [] new_level_nodes;
	}
	return *this;
}

template <typename K, typename V>
Skiplist<K, V>::Skiplist(const Skiplist<K, V>& other) {
	head = nullptr;
	*this = other;
}

template <typename K, typename V>
bool Skiplist<K, V>::get(const K& get_key, V& rtn_value) const {
	Node* node = head;
	for (int level = head->levels - 1; level >= 0; level--) {
		for (; node->nexts[level] != nullptr && node->nexts[level]->key <= get_key; node = node->nexts[level]) {
			if (node->nexts[level]->key == get_key) {
				// get current
				rtn_value = node->nexts[level]->value;
				return true;
			}
		}
	}
	// node not in skiplist
	return false;
}

template <typename K, typename V>
void Skiplist<K, V>::update(const K& update_key, const V& update_value) {
	// keep track of the largest node before going down a level
	Node** prev_nodes = new Node*[head->levels];
	
	Node* node = head;
	for (int level = head->levels - 1; level >= 0; level--) {
		for (; node->nexts[level] != nullptr; node = node->nexts[level]) {
			if (node->nexts[level]->key == update_key) {
				// found node with key
				node->nexts[level]->value = update_value;
				
				delete [] prev_nodes;
				return;
			}
			if (node->nexts[level]->key > update_key) {
				break;
			}
		}
		prev_nodes[level] = node;
		
		
		if (level == 0) {
			// create and insert node
			Node* new_node = new Node(update_key, update_value, getRandomLevels());
			
			// update pointers
			for (int i = 0; i < new_node->levels && i < head->levels; i++) {
				new_node->nexts[i] = prev_nodes[i]->nexts[i];
				prev_nodes[i]->nexts[i] = new_node;
			}
			
			// increase size of nexts
			if (new_node->levels > head->levels) {
				Node** new_nexts = new Node*[new_node->levels];
				// copy old nexts
				for (int i = 0; i < head->levels; i++) {
					new_nexts[i] = head->nexts[i];
				}
				for (int i = head->levels; i < new_node->levels; i++) {
					new_nexts[i] = new_node;
					new_node->nexts[i] = nullptr;
				}
				// replace nexts with new nexts
				delete [] head->nexts;
				head->nexts = new_nexts;
				head->levels = new_node->levels;
			}
			
			delete [] prev_nodes;
			return;
		}
	}
}

template <typename K, typename V>
bool Skiplist<K, V>::remove(const K& remove_key) {
	// keep track of the largest node before going down a level
	Node** prev_nodes = new Node*[head->levels];
	
	Node* node = head;
	for (int level = head->levels - 1; level >= 0; level--) {
		for (; node->nexts[level] != nullptr && node->nexts[level]->key < remove_key; node = node->nexts[level]) {
			// go to lower level if key is larger or next node is to be deleted or next node is nullptr
		}
		prev_nodes[level] = node;
		
		if (level == 0) {
			node = node->nexts[0];
			if (node == nullptr) {
				return false;
			} else if (node->key == remove_key) {
				// update pointers
				for (int i = 0; i < head->levels; i++) {
					if (prev_nodes[i]->nexts[i] == node) {
						prev_nodes[i]->nexts[i] = node->nexts[i];
					}
				}
				delete node;
				
				// check if nexts should be shrinked
				int new_levels = 0;
				for (; new_levels < head->levels; new_levels++) {
					// if (head->nexts[new_levels] == node && head->nexts[new_levels]->nexts[new_levels] == nullptr) {
					if (head->nexts[new_levels] == nullptr) {
						break;
					}
				}
				
				// decrease size of nexts
				if (new_levels != head->levels) {
					Node** new_nexts = new Node*[new_levels];
					for (int i = 0; i < new_levels; i++) {
						new_nexts[i] = head->nexts[i];
					}
					delete [] head->nexts;
					head->nexts = new_nexts;
				}
				
				delete [] prev_nodes;
				return true;
			} else {
				delete [] prev_nodes;
				return false;
			}
		}
	}
	// should never reach this
	return false;
}

template <typename K, typename V>
int Skiplist<K, V>::size() const {
	int count = 0;
	for (Node* node = head->nexts[0]; node != nullptr; node = node->nexts[0], count++);
	return count;
}

template <typename K, typename V>
bool Skiplist<K, V>::empty() const {
	return (head->nexts[0] == nullptr);
}

template <typename K, typename V>
void Skiplist<K, V>::print() const {
	if (size() == 0) {
		cout << "{}" << endl;
	} else {
		cout << "{" << head->nexts[0]->key << ": " << head->nexts[0]->value;
		for (Node* node = head->nexts[0]->nexts[0]; node != nullptr; node = node->nexts[0]) {
			cout << ", " << node->key << ": " << node->value;
		};
		cout << "}" << endl;
	}
}

template <typename K, typename V>
template <typename T>
Skiplist<K, T> Skiplist<K, V>::map(T (*f)(V value)) const {
	Skiplist<K, T> new_skiplist;
	for (Node* node = head->nexts[0]; node != nullptr; node = node->nexts[0]) {
		new_skiplist.update(node->key, f(node->value));
	}
	return new_skiplist;
}

template <typename K, typename V>
Skiplist<K, V> Skiplist<K, V>::filter(bool (*f)(V value)) const {
	Skiplist<K, V> new_skiplist;
	for (Node* node = head->nexts[0]; node != nullptr; node = node->nexts[0]) {
		if (f(node->value)) {
			new_skiplist.update(node->key, node->value);
		}
	}
	return new_skiplist;
}

template <typename K, typename V>
Skiplist<K, V> Skiplist<K, V>::operator+(const Skiplist& other) const {
	Skiplist<K, V> new_skiplist;
	// update this
	for (Node* node = this->head->nexts[0]; node != nullptr; node = node->nexts[0]) {
		new_skiplist.update(node->key, node->value);
	}
	// update other
	for (Node* node = other.head->nexts[0]; node != nullptr; node = node->nexts[0]) {
		new_skiplist.update(node->key, node->value);
	}
	return new_skiplist;
}
