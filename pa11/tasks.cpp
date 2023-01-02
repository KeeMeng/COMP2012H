#include "tasks.h"
#include <iostream>
#include <vector>
using namespace std;

int Tasks::get_total_no_of_children(Dictionary& d) {
	return d.root->total_number_children();
}

void Tasks::zinc_replacement_print_all_elements(Dictionary& d) {
	d.print_all_elements(cout);
}

void Tasks::zinc_replacement_print_elements_given_type(Dictionary& d, const char* type) {
	d.print_elements_given_type(type);
}

Node* Tasks::zinc_replacement_add_node(Dictionary& d, const char* key) {
	return d.add_node(key);
}

void Tasks::run_tasks() {
	int i;
	cin >> i;
	cin.ignore();

	if (1 <= i && i <= 2) {
		tasks1_to_2();
		if (NodeStats::get_nodes_created() != NodeStats::get_nodes_deleted()) {
			cout << "Error: Nodes created (" << NodeStats::get_nodes_created() << ") not equal to nodes deleted (" << NodeStats::get_nodes_deleted() << ")\n";
		} else {
			cout << "Success, nodes created equal to nodes deleted.\n";
		}
	}

	if (11 <= i && i <= 12) {
		tasks11_to_12();
		if (NodeStats::get_nodes_created() != NodeStats::get_nodes_deleted()) {
			cout << "Error: Nodes created (" << NodeStats::get_nodes_created() << ") not equal to nodes deleted (" << NodeStats::get_nodes_deleted() << ")\n";
		} else {
			cout << "Success, nodes created equal to nodes deleted.\n";
		}
	}

	if (13 <= i && i <= 14) {
		tasks13_to_14();
		if (NodeStats::get_nodes_created() != NodeStats::get_nodes_deleted()) {
			cout << "Error: Nodes created (" << NodeStats::get_nodes_created() << ") not equal to nodes deleted (" << NodeStats::get_nodes_deleted() << ")\n";
		} else {
			cout << "Success, nodes created equal to nodes deleted.\n";
		}
	}
}

void Tasks::tasks1_to_2() {
	cout << "ZINC tasks 1-2\n";

	Dictionary d1{""};

	string input;
	while (true) {
		getline(cin, input);
		if (input == "END") {
			break;
		}
		Node* n = Tasks::zinc_replacement_add_node(d1, input.c_str());
		n->meaning.meaning = input;
		n->meaning.type = input;
	}

	// copy constructor
	Dictionary d2{ d1 };
	// check if copy constructor works correctly
	cout << "---------------Printing d1:\n";
	Tasks::zinc_replacement_print_all_elements(d1);
	cout << "---------------Printing d2:\n";
	Tasks::zinc_replacement_print_all_elements(d2);
	delete d2.root;
	d2.root = new Node;
	// check if copy constructor produces a deep copy
	cout << "---------------Printing d1:\n";
	Tasks::zinc_replacement_print_all_elements(d1);
	
	// copy assignment
	while (true) {
		getline(cin, input);
		if (input == "END") {
			break;
		}
		Node* n = Tasks::zinc_replacement_add_node(d2, input.c_str());
		n->meaning.meaning = input;
		n->meaning.type = input;
	}
	d2 = d1;
	// check if copy assignment works correctly
	cout << "---------------Printing d2:\n";
	Tasks::zinc_replacement_print_all_elements(d2);
	delete d2.root;
	d2.root = new Node;
	// check if copy assignment produces a deep copy
	cout << "---------------Printing d1:\n";
	Tasks::zinc_replacement_print_all_elements(d1);
}

void Tasks::tasks11_to_12() {
	cout << "ZINC tasks 11-12\n";

	// merge copy d1 with d2 into d3
	Dictionary d1{""};
	Dictionary d2{""};
	Dictionary dtotal{""};

	string input;
	while (true) {
		getline(cin, input);
		if (input == "END") {
			break;
		}
		Node* n = Tasks::zinc_replacement_add_node(d1, input.c_str());
		n->meaning.meaning = input;
		n->meaning.type = input;

		n = Tasks::zinc_replacement_add_node(dtotal, input.c_str());
		n->meaning.meaning = input;
		n->meaning.type = input;
	}

	while (true) {
		getline(cin, input);
		if (input == "END") {
			break;
		}
		Node* n = Tasks::zinc_replacement_add_node(d2, input.c_str());
		n->meaning.meaning = input;
		n->meaning.type = input;

		n = Tasks::zinc_replacement_add_node(dtotal, input.c_str());
		n->meaning.meaning = input;
		n->meaning.type = input;
	}

	Dictionary d3{ d1.merge(d2) };
	// check if merge works correctly
	cout << "---------------Printing dtotal:\n";
	Tasks::zinc_replacement_print_all_elements(dtotal);
	cout << "---------------Printing d3:\n";
	Tasks::zinc_replacement_print_all_elements(d3);
	delete d3.root;
	d3.root = new Node;
	// check if merge (copy) produces a deep copy
	cout << "---------------Printing d1:\n";
	Tasks::zinc_replacement_print_all_elements(d1);
	cout << "---------------Printing d2:\n";
	Tasks::zinc_replacement_print_all_elements(d2);

	// move merging d3 with d1 should produce no new nodes
	int nodes_created = NodeStats::get_nodes_created();
	// here the move constructor of Dictionary is called, and inside the move merge is called. d3 is empty.
	Dictionary d4 { d3.merge(move(d1)) };
	if (NodeStats::get_nodes_created() - nodes_created <= 8) {
		// tolerance is 8 nodes created. optimally, there is only 1 node created in the constructor used in the implementation of merge.
		cout << "Move test passed\n";
	} else {
		cout << "Move test failed, nodes created: " << (NodeStats::get_nodes_created()-nodes_created) << "\n";
	}
	if (d1.root== nullptr) {
		cout << "Move pointer passed\n";
	} else {
		cout << "Move pointer failed\n";
	}
	cout << "---------------Printing d4:\n";
	Tasks::zinc_replacement_print_all_elements(d4);
}

void Tasks::tasks13_to_14() {
	cout << "ZINC tasks 13-14\n";

	Dictionary d1{""};
	Dictionary d2{""};
	string input;
	while (true) {
		getline(cin, input);
		if (input == "END") {
			break;
		}
		Node* n = d1.add_node(input.c_str());
		n->meaning.meaning = input;
		n->meaning.type = input;
	}

	while (true) {
		getline(cin, input);
		if (input == "END") {
			break;
		}
		Node* n = d2.add_node(input.c_str());
		n->meaning.meaning = input;
		n->meaning.type = input;
	}

	for(int i = 0; i < 5; i++) {
		getline(cin, input);

		int accessed = NodeStats::get_pointers_accessed();
		d1.find_node(input.c_str());
		accessed = NodeStats::get_pointers_accessed() - accessed;
		if (accessed <= (int)input.length()) {
			cout << "Efficiency in find_node achieved.\n";
		} else {
			cout << "Efficiency in find_node violated:   accessed=" << accessed << "  length=" << input.length() << "\n";
		}
	}
	int d1children = d1.root->total_number_children();

	int accessed = NodeStats::get_pointers_accessed();
	cout << d1;
	accessed = NodeStats::get_pointers_accessed() - accessed;
	if (accessed <= 26 * (d1children + 1)) {
		cout << "Efficiency in print_all_elements achieved.\n";
	} else {
		cout << "Efficiency in print_all_elements violated:   accessed=" << accessed << "  cap=" << (26 * (d1children + 1)) << "\n";
	}

	accessed = NodeStats::get_pointers_accessed();
	Dictionary d3 = d1.merge(move(d2));
	accessed = NodeStats::get_pointers_accessed() - accessed;
	if (accessed <= (26 * (d1children + 1) + d1children)) {
		cout << "Efficiency in merge achieved.\n";
	} else {
		cout << "Efficiency in merge violated:   accessed=" << accessed << "  cap=" << (26 * (d1children + 1) + d1children) << "\n";
	}
}