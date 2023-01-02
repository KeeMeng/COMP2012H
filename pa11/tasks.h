#include "dictionary.h"
#include <list>

class Tasks{
	static int get_total_no_of_children(Dictionary& d);
	
	// functions in main.cpp which have to access internal structures.
	static void manipulate_dictionary(std::list<Dictionary*>& ls);
	static void use_dictionary(std::list<Dictionary*>& ls);
	
	friend int main();
	
	// exactly the same function as those in the dictionary.
	// this uses the implementation in the official answer. this is for partial grading.
	static void zinc_replacement_print_all_elements(Dictionary& d);
	static void zinc_replacement_print_elements_given_type(Dictionary& d, const char* type);
	static Node* zinc_replacement_add_node(Dictionary& d, const char* key);
	
	// tasks for zinc. 
	static void run_tasks();
	static void tasks1_to_2();
	static void tasks11_to_12();
	static void tasks13_to_14();
};