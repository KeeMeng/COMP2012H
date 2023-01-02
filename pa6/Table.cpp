#include <fstream>
#include "Table.h"
#include "String.h"
using namespace std;

Table::Table(const String& name) {
	// initialise members
	this->primaryKey = nullptr;
	this->fieldHead = nullptr;
	this->numRows = 0;
	this->numCols = 0;
	this->tableSize = 100;
	this->name = name;
}

Table::Table(ifstream& ifs, const String& name) {
	// initialise members
	this->primaryKey = nullptr;
	this->fieldHead = nullptr;
	ifs >> this->numCols;
	ifs >> this->numRows;
	this->tableSize = 100;
	this->name = name;
	
	if (this->numCols > 0) {
		// read first line of fields
		String line;
		getline(ifs, line, '\n');
		int char_index = 0;
		Field* prev_field = nullptr;
		for (int col = 0; col < this->numCols; col++) {
			Field* field = new Field;
			String field_name = "";
			// check if field starts with *
			if (line[char_index] == '*') {
				this->primaryKey = field;
				char_index++;
			}
			// parse line
			while (line[char_index] != ' ') {
				field_name = field_name + line[char_index++];
			}
			TYPE type = line[++char_index] == '0' ? INT : STRING;
			// add field
			if (col == 0) {
				this->fieldHead = field;
			} else {
				prev_field->next = field;
			}
			prev_field = field;
			field->name = field_name;
			field->next = nullptr;
			field->column = new String[this->tableSize];
			field->type = type;
			// fill with default value
			for (int i = 0; i < this->tableSize; i++) {
				field->column[i] = (type == INT) ? "0" : "";
			}
			
			// skip comma and space after comma
			char_index += 3;
		}
		
		// add record to each column
		for (int row = 0; row < this->numRows; row++) {
			getline(ifs, line, '\n');
			// add comma to end the line
			line = line + ",";
			char_index = 0;
			for (Field* field = this->fieldHead; field != nullptr; field = field->next) {
				String value = "";
				while (line[char_index] != ',') {
					value = value + line[char_index++];
				}
				field->column[row] = value;
				// skip space after comma
				char_index += 2;
			}
		}
	}
}

Table::~Table() {
	if (this->numCols > 0) {
		// set primaryKey to nullptr to prevent delete primary key error
		this->primaryKey = nullptr;
		Field* field = this->fieldHead;
		Field* next_field = field;
		// delete fields from fieldHead
		while (field != nullptr) {
			next_field = field->next;
			this->deleteField(field->name);
			field = next_field;
		}
	}
	this->fieldHead = nullptr;
	this->next = nullptr;
}

void Table::addRecord(int index, String* record) {
	// null pointer
	if (record == nullptr) {
		cout << "Record is empty.\n";
	// dimensions mismatch
	} else if (index > this->numRows || index < 0) {
		cout << "Table row index is out of bounds.\n";
	} else {
		int record_index = 0;
		for (Field* field = this->fieldHead; field != nullptr; field = field->next, record_index++) {
			// primary key error
			if (field == this->primaryKey) {
				if (record[record_index] == "") {
					cout << "Empty or duplicate primary key.\n";
					return;
				}
				for (int i = 0; i < this->numRows; i++) {
					if (record[record_index] == field->column[i]) {
						cout << "Empty or duplicate primary key.\n";
						return;
					}
				}
			}
			
			// Type mismatch
			if (field->type == INT && !isInteger(record[record_index])) {
				cout << "Cannot insert non-integer in integer field.\n";
				return;
			}
		}
		
		// validation passed
		record_index = 0;
		for (Field* field = this->fieldHead; field != nullptr; field = field->next) {
			// add 100 new rows if necessary
			if (this->numRows == this->tableSize - 1) {
				String* old_column = field->column;
				field->column = new String[this->tableSize + 100];
				for (int i = 0; i < this->tableSize; i++) {
					field->column[i] = old_column[i];
				}
				delete [] old_column;
				for (int i = this->tableSize; i < this->tableSize + 100; i++) {
					// fill with default value
					field->column[i] = (field->type == INT) ? "0" : "";
				}
			}
			
			// shift records
			String str = record[record_index++];
			String temp;
			for (int i = index; i < this->numRows; i++) {
				temp = field->column[i];
				field->column[i] = str;
				str = temp;
			}
			field->column[this->numRows] = str;
		}
		
		// update numRows
		this->numRows++;
		if (this->numRows == this->tableSize) {
			this->tableSize += 100;
		}
	}
}

void Table::addField(int index, const String& name, TYPE type) {
	// dimensions mismatch
	if (index > this->numCols || index < 0) {
		cout << "Table column index is out of bounds.\n";
	} else {
		// name error
		for (Field* field = this->fieldHead; field != nullptr; field = field->next) {
			if (field->name == name) {
				cout << "Field with given name already exists in table.\n";
				return;
			}
		}
		
		// create new field
		Field* field;
		if (this->numCols == 0) {
			this->fieldHead = new Field;
			this->primaryKey = this->fieldHead;
			this->fieldHead->next = nullptr;
			field = this->fieldHead;
		} else {
			Field* next_field;
			if (index == 0) {
				next_field = this->fieldHead;
				this->fieldHead = new Field;
				field = this->fieldHead;
			} else {
				// get index field
				field = this->fieldHead;
				for (int i = 0; i < index - 1; i++) {
					field = field->next;
				}
				
				next_field = field->next;
				field->next = new Field;
				field = field->next;
			}
			
			field->next = next_field;
		}
		// initialise members
		field->name = name;
		field->column = new String[this->tableSize];
		field->type = type;
		// fill with default value
		for (int i = 0; i < this->tableSize; i++) {
			field->column[i] = (type == INT) ? "0" : "";
		}
		this->numCols++;
	}
}

void Table::deleteRecord(int row) {
	// dimensions mismatch
	if (row >= this->numRows || row < 0) {
		cout << "Table row index is out of bounds.\n";
	} else {
		// delete record by shifting all values after row down
		for (Field* field = this->fieldHead; field != nullptr; field = field->next) {
			for (int i = row; i < this->numRows - 1; i++) {
				field->column[i] = field->column[i + 1];
			}
			// fill with default value
			field->column[this->numRows - 1] = (field->type == INT) ? "0" : "";
		}
		this->numRows--;
	}
}

void Table::modifyRecord(int row, int column, const String& newVal) {
	// dimensions mismatch
	if (row >= this->numRows || row < 0) {
		cout << "Table row index is out of bounds.\n";
	} else if (column >= this->numCols || column < 0) {
		cout << "Table column index is out of bounds.\n";
	} else {
		Field* field = this->fieldHead;
		for (int i = 0; i < column; i++) {
			field = field->next;
		}
		// primary key error
		if (field == this->primaryKey) {
			if (newVal == "") {
				cout << "Empty or duplicate primary key.\n";
				return;
			}
			for (int i = 0; i < this->numRows; i++) {
				// BUG
				if (i != row) {
					if (newVal == field->column[i]) {
						cout << "Empty or duplicate primary key.\n";
						return;
					}
				}
			}
		}
		// type mismatch
		if (field->type == INT && !isInteger(newVal)) {
			cout << "Cannot insert non-integer in integer field.\n";
			return;
		}
		
		// validation passed
		field->column[row] = newVal;
	}
}

void Table::setPrimaryKey(const String& name) {
	Field* field = this->findField(name);
	if (field == nullptr) {
		// already printed error message
	} else {
		// check for empty
		for (int i = 0; i < this->numRows; i++) {
			if (field->column[i] == "") {
				cout << "Cannot set field with empty data as primary key.\n";
				return;
			}
		}
		// check for duplicates
		for (int i = 0; i < this->numRows; i++) {
			for (int j = i + 1; j < this->numRows; j++) {
				if (field->column[i] == field->column[j]) {
					cout << "Cannot set field with duplicate elements as primary key.\n";
					return;
				}
			}
		}
		
		// validation passed
		this->primaryKey = field;
	}
}

void Table::setColumnIndex(int index, const String& target) {
	Field* field = this->findField(target);
	if (field == nullptr) {
		// already printed error message
	} else if (index >= this->numCols || index < 0) {
		cout << "Table column index is out of bounds.\n";
	} else {
		// remove field from table for now
		if (field == this->fieldHead) {
			this->fieldHead = field->next;
		} else {
			Field* prev_field = this->fieldHead;
			for (; prev_field->next != field; prev_field = prev_field->next);
			prev_field->next = field->next;
		}
		
		// insert field to index
		if (index == 0) {
			field->next = this->fieldHead;
			this->fieldHead = field;
		} else {
			Field* prev_field = this->fieldHead;
			for (int i = 0; i < index - 1; i++) {
				prev_field = prev_field->next;
			}
			field->next = prev_field->next;
			prev_field->next = field;
		}
	}
}

void Table::deleteField(const String& name) {
	Field* delete_field = this->findField(name);
	if (delete_field == nullptr) {
		// already printed error message
	} else {
		if (delete_field == this->primaryKey) {
			cout << "Cannot delete primary key field.\n";
		} else if (delete_field == this->fieldHead) {
			// special case for deleting first item
			this->fieldHead = delete_field->next;
			delete [] delete_field->column;
			delete_field->next = nullptr;
			delete delete_field;
			this->numCols--;
		} else {
			Field* field = this->fieldHead;
			for (; field->next != delete_field; field = field->next);
			Field* next_field = delete_field->next;
			field->next = next_field;
			delete [] delete_field->column;
			delete_field->next = nullptr;
			delete delete_field;
			this->numCols--;
		}
	}
}

Field* Table::findField(const String& name) const {
	for (Field* field = this->fieldHead; field != nullptr; field = field->next) {
		if (field->name == name) {
			return field;
		}
	}
	// did not match any field names
	cout << "No such field with provided name exists.\n";
	return nullptr;
}

void Table::sortTable(Field* field) {
	if (field == nullptr) {
		cout << "Invalid field provided.\n";
	} else {
		// sort by pushing the smallest value to a new column
		String** new_columns = new String*[this->numCols];
		for (int i = 0; i < this->numCols; i++) {
			new_columns[i] = new String[this->numRows];
		}
		
		for (int row = 0; row < this->numRows; row++) {
			// find first row which is not nullstr
			int smallest_row = 0;
			String smallest_value;
			for (int i = 0; i < this->numRows; i++) {
				if (field->column[i] != "nullstr") {
					smallest_row = i;
					smallest_value = field->column[i];
					break;
				}
			}
			// find row with smallest value
			for (int i = smallest_row + 1; i < this->numRows; i++) {
				if (field->column[i] != "nullstr") {
					if ((field->type == INT && stoi(field->column[i]) < stoi(smallest_value)) || (field->type == STRING && field->column[i] < smallest_value)) {
						smallest_value = field->column[i];
						smallest_row = i;
					}
				}
			}
			// add record to new columns
			Field* current_field = this->fieldHead; 
			for (int i = 0; i < this->numCols; i++) {
				new_columns[i][row] = current_field->column[smallest_row];
				current_field = current_field->next;
			}
			// do not use the smallest value again
			field->column[smallest_row] = "nullstr";
		}
		
		// delete old columns and replace with new columns
		Field* current_field = this->fieldHead; 
		for (int i = 0; i < this->numCols; i++) {
			delete [] current_field->column;
			current_field->column = new_columns[i];
			current_field = current_field->next;
		}
		// delete array containing pointers to new columns
		delete [] new_columns;
	}
}


// skeleton code below
bool isInteger(const String& test) {
	if (!test.length() || (test[0] != '-' && !isdigit(test[0]))) {
		return false;
	}
	
	for (int i = 1; i < test.length(); i++) {
		if (!isdigit(test[i])) {
			return false;
		}
	}
	
	return true;
}

String* Table::operator[](int index) const {
	if (index >= numCols || index < 0) {
		cout << "Table column index is out of bounds." << endl;
		return nullptr;
	}

	Field* cur = fieldHead;
	for (int count = 0; count < index; cur = cur->next, count++)
		;
	return cur->column;
}