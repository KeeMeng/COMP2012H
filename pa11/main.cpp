#include <iostream>
#include <list>
#include <vector>
#include <string>
#include "tasks.h"
using namespace std;

// override print functions
bool OVERRIDE_PRINT_FUNCTIONS = false;

void print_help() {
	cout << "Enter the following (without \'): \n";
	cout << "\'list\' to obtain a list of dictionaries\n";
	cout << "\'create\' to create a new dictionary\n";
	cout << "\'delete\' to delete a dictionary\n";
	cout << "\'manipulate\' manipulate a dictionary\n";
	cout << "\'merge\' merge two dictionaries\n";
	cout << "\'filter\' to filter a dictionary\n";
	cout << "\'use\' to use a dictionary\n";
	cout << "\'help\' to list all commands\n";
	cout << "\'end\' to end program\n";
}

/**
 * List all dictionaries.
*/
void list_dictionaries(list<Dictionary*>& ls) {
	cout << "Listing all dictionaries:\n";
	for (list<Dictionary*>::iterator it = ls.begin(); it != ls.end(); it++) {
		cout << (*it)->get_name() << " ";
	}
	cout << "\n";
}

/**
 * Helper function for finding dictionary. Returns ls.end() if none found.
*/
list<Dictionary*>::iterator find_dictionary(const string& name, list<Dictionary*>& ls) {
	list<Dictionary*>::iterator found = ls.end();
	for (list<Dictionary*>::iterator it = ls.begin(); it != ls.end(); it++) {
		if ((*it)->get_name() == name) {
			found = it;
			break;
		}
	}
	return found;
}

/**
 * Prompts the user and creates a dictionary.
 * Assumes the user does not enter an empty string.
 * If the name already exists, inform the user and do not create.
*/
void create_dictionary(list<Dictionary*>& ls) {
	cout << "Enter the name for dictionary:\n";

	string input;
	getline(cin, input);
	list<Dictionary*>::iterator found = find_dictionary(input, ls);
	if (found != ls.end()) {
		cout << "Name already exists! Could not create dictionary.\n";
	} else {
		Dictionary* d = new Dictionary{input};
		ls.push_back(d);
		cout << "Dictionary created: " << input << "\n";
	}
}

/**
 * Prompts the user and deletes the dictionary with the given name.
 * Assumes the user does not enter an empty string.
 * If the name doesn't exist, inform the user and do not delete.
*/
void delete_dictionary(list<Dictionary*>& ls) {
	cout << "Enter the name for dictionary:\n";
	string input;
	getline(cin, input);

	list<Dictionary*>::iterator found = find_dictionary(input, ls);
	if (found != ls.end()) {
		delete *found;
		ls.erase(found);
		cout << "Deleted dictionary with name " << input << "\n";
	} else {
		cout << "Could not find dictionary with the above name.\n";
	}
}

void manipulate_dictionary_add_key(Dictionary &d) {
	string word;
	cout << "Enter word to be added / updated:\n";
	getline(cin, word);
	if (word.empty()) {
		cout << "Cannot add word with empty string.\n";
		return;
	}
	
	string type;
	cout << "Enter type of word:\n";
	getline(cin, type);

	string meaning;
	cout << "Enter meaning of word:\n";
	getline(cin, meaning);

	Node* n = d += word.c_str();
	n->meaning.meaning = meaning;
	n->meaning.type = type;

	cout << "Updated the word \'" << word << "\' to the dictionary\n";
}

/**
 * Prompts the user and removes all nodes starting with the key inputted by the user (if exists).
*/
void manipulate_dictionary_remove_entry(Dictionary &d) {
	cout << "Enter word to be removed:\n";
	string key;
	getline(cin, key);

	d -= key.c_str();

	cout << "Removed all nodes starting with \'" << key << "\'\n";
}

void Tasks::manipulate_dictionary(list<Dictionary*>& ls) {
	cout << "Enter the name for dictionary:\n";
	string input;
	getline(cin, input);

	list<Dictionary*>::iterator found = find_dictionary(input, ls);

	if (found == ls.end()) {
		cout << "Could not find dictionary with above name.\n";
		return;
	}

	Dictionary &d = **found;
	
	bool subroutine_running = true;
	while (subroutine_running) {
		cout << "\n\n\n\n";
		cout << "Enter the following:\n";
		cout << "\'1\' to print the tree structure of the dictionary.\n";
		cout << "\'2\' to print all words of the dictionary.\n";
		cout << "\'3\' to add a key to the dictionary.\n";
		cout << "\'4\' to remove an entry from the dictionary.\n";
		cout << "\'5\' to exit this subroutine.\n";

		int command;
		cin >> command;
		cin.ignore();
		switch (command) {
			case 1:
				cout << "Total number of children of " << d.get_name() <<" (excluding root): " << Tasks::get_total_no_of_children(d) << "\n";
				if (OVERRIDE_PRINT_FUNCTIONS) {
					Tasks::zinc_replacement_print_all_elements(d);
				} else {
					cout << d;
				}
				break;
			case 2:
				if (OVERRIDE_PRINT_FUNCTIONS) {
					Tasks::zinc_replacement_print_elements_given_type(d, nullptr);
				} else {
					d.print_elements_given_type(nullptr);
				}
				break;
			case 3:
				manipulate_dictionary_add_key(d);
				break;
			case 4:
				manipulate_dictionary_remove_entry(d);
				break;
			case 5:
				subroutine_running = false;
				cout << "Going back to main routine:\n\n";
				break;
		}
	}
}

/**
 * Prompts the user and creates a dictionary.
 * Assumes the user does not enter an empty string.
 * If the name already exists, inform the user and do not create.
*/
void merge_dictionary(list<Dictionary*>& ls) {
	cout << "Enter the name for first dictionary:\n";

	string input;
	getline(cin, input);
	list<Dictionary*>::iterator d1 = find_dictionary(input, ls);
	if (d1 == ls.end()) {
		cout << "Dictionary not found! Could not merge dictionary.\n";
		return;
	}
	cout << "Enter the name for second dictionary:\n";
	getline(cin, input);
	list<Dictionary*>::iterator d2 = find_dictionary(input, ls);
	if (d2 == ls.end()) {
		cout << "Dictionary not found! Could not merge dictionary.\n";
		return;
	}
	cout << "Enter the name for the new dictionary:\n";
	getline(cin, input);
	list<Dictionary*>::iterator d = find_dictionary(input, ls);
	if (d != ls.end()) {
		cout << "Dictionary already exists! Could not merge dictionary.\n";
		return;
	}

	Dictionary &dict1 = **d1;
	Dictionary &dict2 = **d2;
	Dictionary *dict = new Dictionary{dict1.merge(dict2)};
	dict->set_name(input);

	ls.push_back(dict);
	cout << "Created dictionary " << input << " by merging.\n";
}

/**
 * Prompts the user and creates a dictionary.
 * Assumes the user does not enter an empty string.
 * If the name already exists, inform the user and do not create.
*/
void filter_dictionary(list<Dictionary*>& ls) {
	cout << "Enter the name for first dictionary:\n";

	string input;
	getline(cin, input);
	list<Dictionary*>::iterator d = find_dictionary(input, ls);
	if (d == ls.end()) {
		cout << "Dictionary not found! Could not filter dictionary.\n";
		return;
	}
	cout << "Enter the name for the new dictionary:\n";
	getline(cin, input);
	list<Dictionary*>::iterator d2 = find_dictionary(input, ls);
	if (d2 != ls.end()) {
		cout << "Dictionary already exists! Could not filter dictionary.\n";
		return;
	}

	Dictionary &dict1 = **d;

	string word;
	cout << "Enter word to be filtered:\n";
	getline(cin, word);

	Dictionary *dict = new Dictionary{dict1.filter_starting_word(word.c_str())};
	dict->set_name(input);

	ls.push_back(dict);
	cout << "Created dictionary " << input << " by filtering.\n";
}

/**
 * Prompts the user and creates a dictionary.
 * Assumes the user does not enter an empty string.
 * If the name already exists, inform the user and do not create.
*/
void Tasks::use_dictionary(list<Dictionary*>& ls) {
	cout << "Enter the name for dictionary:\n";

	string input;
	getline(cin, input);
	list<Dictionary*>::iterator found = find_dictionary(input, ls);
	if (found == ls.end()) {
		cout << "Dictionary not found! Could not use dictionary.\n";
		return;
	}
	
	Dictionary &dict = **found;
	string filter = "";

	while (true) {
		cout << "\n\n\n\n";
		cout << "CURRENT FILTER: " << filter << "\n";
		cout << "The following commands are available for using dictionary:\n";
		cout << "\'lookup\' to lookup for a specific word in dictionary\n";
		cout << "\'suggest\' to find all words starting with the given word\n";
		cout << "\'encrypt\' prints out all words encrypted by Caesar cipher with shift 5\n";
		cout << "\'setfilter\' set the filter of word type\n";
		cout << "\'end\' Stop searching this dictionary\n";
		getline(cin, input);

		if (input == "lookup") {
			cout << "Enter text for lookup:\n";
			getline(cin, input);

			Node* node = dict.find_node(input.c_str());
			if (node == nullptr) {
				cout << "No such word in dictionary!\n";
			} else {
				cout << "Word \'" << input << "\' found.\n";
				cout << "Type: " << node->meaning.type << "\n";
				cout << "Meaning: " << node->meaning.meaning << "\n";
			}
		} else if (input == "suggest") {
			cout << "Enter text for suggestion:\n";
			getline(cin, input);
			cout << "Found words:\n";
			Dictionary subdict = dict.filter_starting_word(input.c_str());
			if (filter.empty()) {
				if (OVERRIDE_PRINT_FUNCTIONS) {
					Tasks::zinc_replacement_print_elements_given_type(subdict, nullptr);
				} else {
					subdict.print_elements_given_type(nullptr);
				}
			} else {
				if (OVERRIDE_PRINT_FUNCTIONS) {
					Tasks::zinc_replacement_print_elements_given_type(subdict, filter.c_str());
				} else {
					subdict.print_elements_given_type(filter.c_str());
				}
			}
		} else if (input == "setfilter") {
			cout << "Enter word type filter (directly press enter for empty filter):\n";
			getline(cin, filter);
		} else if (input == "encrypt") {
			cout << "Words in dictionary:\n";
			lambda_for_main_cpp count; // see definition below
			count.count = 1;
			dict.foreach(count);
			// We cannot use lambda in this case since the templates are instantiated in different compilation units. 
			// Correct implementation for lambda:
			/*
			dict.foreach([&count](Node* current_node, vector<int>& current_key)->void{
				for (vector<int>::iterator it = current_key.begin(); it != current_key.end(); it++) {
					cout << (char)((*it) + 5);
				}
				cout << " [" << count << "]\n";
				++count;
			});
			*/
		} else if (input == "end") {
			cout << "Going back to main routine:\n\n";
			break;
		}
	}
}

void lambda_for_main_cpp::operator()(Node* current_node, vector<int>& current_key) {
	if (!current_node->meaning.meaning.empty()) {
		for (vector<int>::iterator it = current_key.begin(); it != current_key.end(); it++) {
			cout << (char)( ((*it) + 5)%26 + 97 );
		}
		cout << " [" << count << "]\n";
		count++;
	}
}

int main() {
	OVERRIDE_PRINT_FUNCTIONS = false;
	list<Dictionary*> list;

	bool tasks = false;

	// Main loop:
	bool program_running = true;

	print_help();

	while (program_running) {
		string input;
		getline(cin, input);

		if (input == "help") {
			print_help();
		} else if (input == "list") {
			list_dictionaries(list);
		} else if (input == "create") {
			create_dictionary(list);
		} else if (input == "delete") {
			delete_dictionary(list);
		} else if (input == "manipulate") {
			Tasks::manipulate_dictionary(list);
		} else if (input == "merge") {
			merge_dictionary(list);
		} else if (input == "filter") {
			filter_dictionary(list);
		} else if (input == "use") {
			Tasks::use_dictionary(list);
		} else if (input == "end") {
			program_running = false;
		} else if (input == "OVERRIDE") {
			OVERRIDE_PRINT_FUNCTIONS = !OVERRIDE_PRINT_FUNCTIONS;
		} else if (input == "TASKS") {
			tasks = true;
			program_running = false;
		}
	}

	for (std::list<Dictionary*>::iterator it = list.begin(); it != list.end(); it++) {
		delete *it;
	}

	if (tasks) {
		Tasks::run_tasks();
	} else {
		//NodeStats::print_statistics();
	}
	return 0;
}