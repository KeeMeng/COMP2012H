const int CHUNK_SIZE = 8;

struct Node {
	int arr[CHUNK_SIZE];	// the chunk
	Node* prev;				// previous Node
	Node* next;				// next Node
};

struct Iterator {
	int* current;			// current position
	int* first;				// begin of the chunk, i.e., the position of first item
	int* last;				// end of the chunk, i.e., the position after the last item
	const Node* node;		// current Node
};

struct Deque {
	Iterator start;			// the position of first item in deque
	Iterator end;			// the position after last item in deque

	Node* sentinel;			// sentinel of the circular doubly-linked list
	int ll_size;			// size of linked list, notice that this is number of chunks, not items
};